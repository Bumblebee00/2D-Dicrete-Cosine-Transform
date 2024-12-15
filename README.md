This code performs the [2-d Discrete Cosine Transform](https://en.wikipedia.org/wiki/Discrete_cosine_transform#Multidimensional_DCTs) on images. It can save to disk the spectrum of a image in png or binary format, and it can perform the inverse DCT to reconstruct the image from the spectrum (or a modified version of it). It can also generate the basis images for a certain width and height, by performig the inverse DCT on spectums with only one non-zero element.

Here are some images generated from various spectra:

Decription | Spectrum | Image
:-:|:-:|:-:
original image | ![](gorilla_spectrum.png)  |  ![](gorilla_gray.png)
only high frequencies | ![](gorilla_modified_spectrum.png) | ![](gorilla_output.png)
original image | ![](g_spectrum.png)  |  ![](g_gray.png)
ony low frequencies | ![](g_modified_spectrum0.png) | ![](g_output0.png)
no low frequencies | ![](g_modified_spectrum1.png) | ![](g_output1.png)
no low e medium frequencies | ![](g_modified_spectrum2.png) | ![](g_output2.png)
no horizontal low frequencies | ![](g_modified_spectrum3.png) | ![](g_output3.png)
no vertical low frequencies | ![](g_modified_spectrum4.png) | ![](g_output4.png)
only high frequencies | ![](g_modified_spectrum5.png) | ![](g_output5.png)
only low horizontal and high vertical frequencies | ![](g_modified_spectrum6.png) | ![](g_output6.png)
only high horizontal and low vertical frequencies | ![](g_modified_spectrum7.png) | ![](g_output7.png)