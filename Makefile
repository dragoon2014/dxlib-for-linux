SHELL := /bin/bash

DXLIB_VER := 3_22e

# 環境によっては変更してください
RENAME := rename.ul
UNZIP := unzip
NKF := nkf

# 環境、要不要に応じて変更してください
CXXFLAGS := -g -O0 \
-DDX_NON_BULLET_PHYSICS \
-DDX_NON_LIVE2D_CUBISM4 \
-I insufficient_include \
-I /usr/include/opus \
#-I clib/prefix/include \
#-I clib/prefix/include/opus \
#-DDX_NON_JPEGREAD \
#-DDX_NON_TIFFREAD \
#-DDX_NON_PNGREAD \
#-DDX_NON_MODEL \
#-DDX_NON_OGGVORBIS \

# 要不要に応じて変更してください
DEP_LIBS := \
    EGL GL X11 \
    jpeg ogg openal opus opusfile opusurl \
    png pthread theora theoradec theoraenc tiff tiffxx \
    vorbis vorbisenc vorbisfile z \

LDFLAG_LIBS := $(addprefix -l, $(DEP_LIBS))

SRCS := $(addprefix DxLibMake/,\
        DxASyncLoad \
        DxArchive_ \
        DxChar \
        DxCharCodeTable \
        DxGateway \
        DxHandle \
        DxHeap \
        DxInputString \
        DxLive2DCubism4 \
        DxMath \
        DxMemImg \
        DxMemImgDrawFunction0 \
        DxMemImgDrawFunction1 \
        DxMemImgDrawFunction2 \
        DxMemImgDrawFunction3 \
        DxModelLoader0 \
        DxModelLoader1 \
        DxModelLoader2 \
        DxModelLoader3 \
        DxModelLoader4 \
        DxModelLoaderVMD \
        DxModelRead \
        DxRingBuffer \
        DxSoftImage \
        DxUseCLib \
        DxUseCLibPhysics \
        Linux/DxBaseFuncLinux       DxBaseFunc \
        Linux/DxBaseImageLinux      DxBaseImage \
        Linux/DxFileLinux           DxFile \
        Linux/DxFontLinux           DxFont \
        Linux/DxGraphicsLinux       DxGraphics \
        Linux/DxGraphicsFilterLinux DxGraphicsFilter \
        Linux/DxInputLinux          DxInput \
        Linux/DxLive2DCubism4Linux  DxUseCLibLive2DCubism4 \
        Linux/DxLogLinux            DxLog \
        Linux/DxMaskLinux           DxMask \
        Linux/DxMemoryLinux         DxMemory \
        Linux/DxModelLinux          DxModel \
        Linux/DxMovieLinux          DxMovie \
        Linux/DxSoundLinux          DxSound \
        Linux/DxSoundConvertLinux   DxSoundConvert \
        Linux/DxSystemLinux         DxSystem \
        Linux/DxThreadLinux         DxThread \
        Linux/DxUseCLibOggLinux     DxUseCLibOgg \
        Linux/DxShaderCodeBin_Base3D_Linux \
        Linux/DxShaderCodeBin_Base_Linux \
        Linux/DxShaderCodeBin_Filter_Linux \
        Linux/DxShaderCodeBin_Model_Linux \
        Linux/DxShaderCodeBin_RgbaMix_Linux \
        Linux/DxWindowLinux \
    )

OBJS := $(addsuffix .o,$(SRCS))

SAMPLES := $(addprefix samples/,\
        sample01_minimum \
        sample02_string_and_shape \
        sample03_3d_shape \
        sample04_mainloop \
        sample05_sound \
        sample06_graph \
        sample07_printfdx \
        sample08_input \
        sample09_window \
    )

.PHONY: all
all: $(SAMPLES)

$(SAMPLES): lib
	g++ -o $@ $@.cpp \
    -I DxLibMake $(CXXFLAGS) \
    DxLibMake/libDxLib.a \
    $(LDFLAG_LIBS) \

.PHONY: lib
lib: $(OBJS)
	rm -f DxLibMake/libDxLib.a
	ar rcs DxLibMake/libDxLib.a $(OBJS)

.cpp.o: patch
	g++ -o $@ -c $< $(CXXFLAGS)

.PHONY: patch
patch: extract-source
	# 上流バグ対応:終了判定変数名ミス
	patch -uNp1 --no-backup-if-mismatch -d . < pre-0001-wrong-varname-for-finalize.patch
	# 上流バグ対応:クリティカルセクション解放忘れ
	patch -uNp1 --no-backup-if-mismatch -d . < pre-0002-forgot-unlock-critical-section.patch
	# 上流バグ対応:#endifのコメントアウト忘れ
	patch -uNp1 --no-backup-if-mismatch -d . < pre-0003-should-comment-out-endif.patch
	# 上流改良:jinclude.hへの依存解除
	patch -uNp1 --no-backup-if-mismatch -d . < pre-0004-no-longer-required-jinclude-h.patch
	
	# Linux用コンパイル設定追加
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0001-DxCompileConfig.patch
	# Linux向け型定義
	cp -a DxLibMake/DxDataType{Android,Linux}.h
	# 不足ヘッダー追加
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0003-DxDataTypeLinux.patch
	
	# AndroidをベースにLinux用のコードを生成
	#  単純にコピー
	cp -a DxLibMake/Android DxLibMake/Linux
	#  ファイル名をAndroid->Linux
	$(RENAME) Android Linux DxLibMake/Linux/*
	#  各種Androidっぽい字句->対応するLinuxっぽい字句
	sed -i \
    -e s/Android/Linux/g \
    -e s/ANDROID/LINUX/g \
    -e s/android/linux/g \
    -e s/GANDR/GLINUX/g \
    -e s/ANDR/LINUX/g \
    DxLibMake/Linux/*.{h,cpp}
	# iOSをベースにするコードを上書き
	for f in \
            DxFile:h \
            DxFile:cpp \
            DxFont:h \
            DxFont:cpp \
            DxLog:h \
            DxLog:cpp \
            DxSound:h \
            DxSound:cpp \
            ; do \
        IFS=: f=($${f}); \
        cat DxLibMake/iOS/$${f[0]}iOS.$${f[1]} | sed \
            -e s/IOS/LINUX/g \
            -e s/iOS/Linux/g \
            > DxLibMake/Linux/$${f[0]}Linux.$${f[1]} ; \
    done
	#  Linuxで利用しないコードの削除
	rm -f DxLibMake/Linux/DxJavaLinux.h

	#  各ヘッダ内でLinux向けのifdefを追加
	for f in \
            DxBaseFunc.h:Linux/DxBaseFuncLinux.h \
            DxBaseImage.cpp:Linux/DxBaseImageLinux.h \
            DxDataType.h:DxDataTypeLinux.h \
            DxFile.h:Linux/DxFileLinux.h \
            DxFont.cpp:Linux/DxFontLinux.h \
            DxGraphics.cpp:Linux/DxGraphicsLinux.h \
            DxGraphicsFilter.cpp:Linux/DxGraphicsFilterLinux.h \
            DxInput.h:Linux/DxInputLinux.h \
            DxLib.h:DxFunctionLinux.h \
            DxLive2DCubism4.h:Linux/DxLive2DCubism4Linux.h \
            DxLog.h:Linux/DxLogLinux.h \
            DxMask.cpp:Linux/DxMaskLinux.h \
            DxMemory.h:Linux/DxMemoryLinux.h \
            DxModel.cpp:Linux/DxModelLinux.h \
            DxMovie.h:Linux/DxMovieLinux.h \
            DxSound.h:Linux/DxSoundLinux.h \
            DxSoundConvert.h:Linux/DxSoundConvertLinux.h \
            DxSystem.h:Linux/DxSystemLinux.h \
            DxThread.h:Linux/DxThreadLinux.h \
            DxUseCLibOgg.cpp:Linux/DxUseCLibOggLinux.h \
            ; do \
        IFS=: f=($${f}); \
        echo -e "\n#ifdef __linux__\n#include \"$${f[1]}\"\n#endif // __linux__" | \
        sed -i -e '/\/\/ __ANDR/r/dev/stdin' DxLibMake/$${f[0]} ; \
    done
	
	#  なんかバグい
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0011-not-work-printfDxBase_WCHAR_T.patch
	#  名前干渉
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0012-Always-already-defined.patch
	#  Linux専用関数
	cp -a DxFunctionLinux.h DxLibMake
	cp -a DxWindowLinux.h DxLibMake/Linux
	cp -a DxWindowLinux.cpp DxLibMake/Linux
	#  Android特化コードを削除
	cp -a DxSystemLinux.h DxLibMake/Linux
	cp -a DxInputLinux.h DxLibMake/Linux
	#  微修正
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0100-File-cpp.patch
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0100-Log-cpp.patch
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0100-Sound-h.patch
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0100-Sound-cpp.patch
	patch -uNp1 --no-backup-if-mismatch -d DxLibMake < 0100-Thread-cpp.patch
	#  (Androidベース、要分離)
	cp -a DxSystemLinux.cpp DxLibMake/Linux
	#  (要分離)
	cp -a DxGraphicsLinux.h DxLibMake/Linux
	cp -a DxGraphicsLinux.cpp DxLibMake/Linux
	#  Android特化コードを削除
	cp -a DxInputLinux.cpp DxLibMake/Linux
	#  (iOSベース？)
	cp -a DxFontLinux.cpp DxLibMake/Linux
	
	@# debug
	@#rm -rf DxLibMake.old DxLibMake.new
	@#cp -ai DxLibMake{,.old}
	@#cp -ai DxLibMake{,.new}



.PHONY: extract-source
extract-source: get-source
	rm -rf DxLibMake
	$(UNZIP) -O cp932 DxLibMake$(DXLIB_VER).zip
	find DxLibMake -type f -exec $(NKF) -w -Lu --overwrite {} +

.PHONY: get-source
get-source:
	[ -f "DxLibMake$(DXLIB_VER).zip" ] || \
    wget -nc https://dxlib.xsrv.jp/DxLib/DxLibMake$(DXLIB_VER).zip

.PHONY: clean
clean:
	rm -rf DxLibMake
	rm -f $(SAMPLES)

.PHONY: clean_all
clean_all: clean
	rm DxLibMake*.zip
