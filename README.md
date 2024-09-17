# Image Editor - Project Overview

**Author**: Alexandru-Andrei Ionita    
**Year**: 2022-2023  
**Source Files**: `main.c`, `apply.h`, `case.h`, `crop.h`, `exitfile.h`, `histogram.h`, `load.h`, `save.h`, `select.h`, `struct.h`

---

## 🖼️ Project Description

The **Image Editor** is a powerful and efficient command-line image processing tool built in C, designed to work with images in the **NetPBM format** (PPM and PGM). The editor enables users to perform essential image manipulations, such as loading, saving, cropping, applying filters, and more, by interpreting and executing commands. The editor handles images in grayscale and full RGB color, supporting both ASCII and binary encoding.

This project is a showcase of the fundamental algorithms and techniques used in modern image processing software, such as Adobe Photoshop, but implemented in a simplified, text-based interface. The editor operates efficiently on large images through dynamic memory allocation and ensures proper resource management.

---

## 🔍 Key Algorithms and Techniques

### 1. **Command Parsing**  
At the core of the image editor is a **command parser** that processes input strings and directs the program to perform various image manipulations. The parser utilizes string handling functions to interpret the command and parameters, guiding the control flow to the relevant operation.

### 2. **Matrix Representation of Images**
All images are stored as **matrices**, where each pixel is represented as either a grayscale value (in PGM) or as three separate values for red, green, and blue (in PPM). Operations such as cropping, transposing, and applying filters are performed by manipulating these matrices. This matrix-centric design allows for efficient processing and transformation of images.

### 3. **Dynamic Memory Management**
The program dynamically allocates memory for image matrices, ensuring that it can handle images of varying sizes efficiently. Proper memory management is employed throughout the application, with checks for memory allocation failures, and all resources are freed upon exit to prevent memory leaks.

### 4. **Image Filters via Kernel Convolution (APPLY Command)**
The **APPLY** command implements popular image filters such as **EDGE detection**, **BLUR**, **GAUSSIAN BLUR**, and **SHARPEN** using **kernel convolution algorithms**. The kernel is a small matrix that is applied to each pixel and its neighbors to compute the new pixel value. The process involves:

- **Convolution**: The values of neighboring pixels are multiplied by the kernel values, and the sum becomes the new pixel value.
- **Edge Handling**: Pixels at the edges of the image are treated carefully to ensure that transformations do not distort the overall image.
- **Clamping**: After the convolution process, pixel values are clamped between 0 and 255 to ensure valid image output, preventing overflow or underflow.

### 5. **Cropping and Selection**
The **CROP** command allows users to reduce the image to a specific rectangular region, removing any data outside of the selection. The **SELECT** command defines the region of interest, and the crop operation is executed on this selection. This is achieved by iterating through the matrix and retaining only the pixels within the selected coordinates.

### 6. **Histogram Calculation and Image Equalization**
The **histogram** functionality computes the distribution of pixel intensities across the image. Histograms are crucial for understanding the contrast and brightness of an image. The **equalization algorithm** enhances the image contrast by redistributing the intensity values, improving visibility in underexposed or overexposed images.

- **Histogram Equalization**: The pixel intensity distribution is adjusted based on the histogram, producing a more balanced image with improved contrast.
- **Dynamic Range**: The algorithm stretches the intensity values across the available range, ensuring that the full range from 0 to 255 is utilized.

### 7. **Rotation (Bonus Feature)**
The **ROTATE** command (optional) rotates the selected region of the image by specified angles (90°, 180°, 270°). Rotation is performed by transposing the matrix and then reversing rows or columns, depending on the angle.

---

## 🛠️ Program Workflow

1. **Loading Images**:  
   The `LOAD` command loads a PGM or PPM image into memory, automatically selecting the entire image for further operations. It supports both ASCII and binary formats.

2. **Image Manipulation**:  
   Users can **select** specific regions of the image using the `SELECT` command, which defines a rectangular region. The `SELECT ALL` command resets the selection to include the entire image. 

3. **Cropping and Transforms**:  
   Once a region is selected, the user can **crop** the image to retain only the selected portion. The `CROP` command removes all other parts of the image outside the selection.

4. **Applying Filters**:  
   The `APPLY` command applies various filters to the image based on the selected region. Filters are implemented through **convolution with a kernel**, which alters pixel values based on neighboring pixel data. The supported filters include:
   - **EDGE**: Detects and highlights edges in the image.
   - **BLUR**: Softens the image by averaging nearby pixels.
   - **GAUSSIAN BLUR**: A more complex blur that produces a natural smoothing effect.
   - **SHARPEN**: Enhances edges and details in the image.

5. **Saving Images**:  
   The `SAVE` command saves the edited image to a file in either binary or ASCII format. The image can be saved at any point during the editing process.

6. **Exiting**:  
   The `EXIT` command gracefully terminates the program, ensuring all memory allocations are freed, preventing memory leaks.

---

## 🖼️ Image Formats Supported

The program supports the **NetPBM** image formats:
- **PGM** (Portable GrayMap) for grayscale images.
- **PPM** (Portable PixMap) for color images.

Both formats can be handled in **ASCII** and **binary** encoding. The editor processes images with up to 255 intensity levels per channel (8-bit depth).

---

## 📊 Histogram and Equalization

Histograms display the distribution of pixel values, and the **histogram equalization** feature improves image contrast by balancing the distribution. For grayscale images, the program calculates and displays histograms with user-defined bin sizes and maximum display bars.

---

## ⚙️ Performance and Efficiency

- **Dynamic Memory Allocation**: The program manages memory efficiently, ensuring it can handle large images without excessive memory consumption. Only two copies of an image are stored in memory at any given time.
- **Efficient Command Parsing**: Each command is parsed and executed in constant time, with operations like convolution and cropping optimized for performance.

---

## Conclusion

The **Image Editor** demonstrates robust image manipulation through well-implemented algorithms such as kernel convolution, cropping, and histogram equalization. The project emphasizes memory management, efficient command parsing, and matrix-based operations, making it a reliable and scalable tool for basic image editing tasks.
