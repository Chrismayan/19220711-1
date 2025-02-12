from PIL import Image


pic = Image.open(
    "C:/Users/王欣哲/Desktop/2.png").convert('L').resize((96, 96), Image.ANTIALIAS)
pic.save("C:/Users/王欣哲/Desktop/2-2.png")
