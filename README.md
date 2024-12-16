This code performs the [2D Discrete Cosine Transform](https://en.wikipedia.org/wiki/Discrete_cosine_transform#Multidimensional_DCTs) on images. It can save to disk the spectrum of a image in png or binary format, and it can perform the inverse DCT to reconstruct the image from the spectrum (or a modified version of it). It can also generate the basis images for a certain width and height, by performig the inverse DCT on spectums with only one non-zero element.

Here are some images generated from various spectra:

Decription | Spectrum | Image
:-:|:-:|:-:
original image | ![](gorilla_spectrum.png)  |  ![](gorilla_gray.png)
no low frequencies | ![](gorilla_modified_spectrum.png) | ![](gorilla_output.png)
original image | ![](pavimento_spectrum.png) | ![](pavimento_gray.png)
no high vertical frequencies | ![](pavimento_modified_spectrum1.png) | ![](pavimento_output1.png)
no high horizontal frequencies | ![](pavimento_modified_spectrum2.png) | ![](pavimento_output2.png)
original image | ![](pavimentozoom_spectrum.png) | ![](pavimentozoom_gray.png)
original image | ![](g_spectrum.png)  |  ![](g_gray.png)
ony low frequencies | ![](g_modified_spectrum0.png) | ![](g_output0.png)
no low frequencies | ![](g_modified_spectrum1.png) | ![](g_output1.png)
only high frequencies | ![](g_modified_spectrum2.png) | ![](g_output2.png)
only very high frequencies | ![](g_modified_spectrum5.png) | ![](g_output5.png)
removed low frequences and high vertical frequences | ![](g_modified_spectrum3.png) | ![](g_output3.png)
removed low frequences and high horizontal frequences | ![](g_modified_spectrum4.png) | ![](g_output4.png)
??? | ![](g_modified_spectrum6.png) | ![](g_output6.png)
??? | ![](g_modified_spectrum7.png) | ![](g_output7.png)

the gorilla took 15 minutes to spectralize.
