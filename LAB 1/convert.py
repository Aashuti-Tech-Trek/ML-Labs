import cv2
import numpy as np

# Read image in grayscale
img = cv2.imread("image.png", cv2.IMREAD_GRAYSCALE)

if img is None:
    print("Could not open or find the image!")
    exit()

print("Original Width:", img.shape[1])
print("Original Height:", img.shape[0])

# Downsample image (VERY IMPORTANT)
img = cv2.resize(img, (200, 200))   # 100x100 is ideal for labs

print("Resized Width:", img.shape[1])
print("Resized Height:", img.shape[0])

# Save resized image to CSV
np.savetxt("image_output.csv", img, delimiter=",", fmt="%d")

print("Image saved successfully as image_output.csv")
