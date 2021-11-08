- bbball.png とその派生
  以下から入手できます。ライセンスはパブリックドメインです。
    https://commons.wikimedia.org/wiki/File:Animated_PNG_example_bouncing_beach_ball.png
  bbball_01〜20.png（リポジトリにはないです）は以下で生成できます。
    ffmpeg -i bbball.png -vcodec png bbball_%02d.png
  bbball_tiled.pngは続けて以下で生成できます。
    ffmpeg -i bbball_%02d.png -filter_complex tile=5x4 bbball_tiled.png
  bbball.webmは以下で生成できます。
    ffmpeg -i bbball.png bbball.webm

- noise.ogg
  以下で生成できます。ライセンスはパブリックドメインです。
    ffmpeg -f lavfi -i 'anoisesrc=c=brown:d=5:a=0.5:r=48000' noise.ogg
