
from PIL import Image, ImageFont, ImageDraw, BdfFontFile

# run the onverter wihtou the script ududufu
with open("font/spleen-8x16.bdf", "rb") as f:
    p = BdfFontFile.BdfFontFile(f)
    p.save("font/font.pil")

# generate mega character string
allchars = ""
for c in range(32, 127):
    allchars += chr(c)

image = Image.new("RGBA", (95*8, 16))
draw = ImageDraw.Draw(image)
font = ImageFont.load('font/font.pil')
draw.text((0,0), allchars, font=font)
image.save("font/font.png")

