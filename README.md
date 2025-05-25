`main.c` performs the [2D Discrete Cosine Transform](https://en.wikipedia.org/wiki/Discrete_cosine_transform#Multidimensional_DCTs) on images.

$$
X_{k_1,k_2} = \sum_{n_1=0}^{N_1 - 1} \sum_{n_2=0}^{N_2 - 1} x_{n_1,n_2} 
\cos\left[ \frac{\pi}{N_1} \left(n_1 + \frac{1}{2} \right) k_1 \right] 
\cos\left[ \frac{\pi}{N_2} \left(n_2 + \frac{1}{2} \right) k_2 \right].
$$

It can save to disk the spectrum of a image in png or binary format, and it can perform the inverse DCT to reconstruct the image from the spectrum (or a modified version of it). It can also generate the basis images for a certain width and height, by performig the inverse DCT on spectums with only one non-zero element.

Here are some images generated from various spectra:

Decription | Spectrum | Image
:-:|:-:|:-:
original image | ![](gorilla/gorilla_spectrum.png)  |  ![](gorilla/gorilla_gray.png)
no low frequencies | ![](gorilla/gorilla_modified_spectrum.png) | ![](gorilla/gorilla_output.png)
original image | ![](pavimento/pavimento_spectrum.png) | ![](pavimento/pavimento_gray.png)
no high vertical frequencies | ![](pavimento/pavimento_modified_spectrum1.png) | ![](pavimento/pavimento_output1.png)
no high horizontal frequencies | ![](pavimento/pavimento_modified_spectrum2.png) | ![](pavimento/pavimento_output2.png)
original image | ![](pavimentozoom/pavimentozoom_spectrum.png) | ![](pavimentozoom/pavimentozoom_gray.png)
original image | ![](palace/palace_spectrum.png) | ![](palace/palace_gray.png)
original image | ![](g/g_spectrum.png)  |  ![](g/g_gray.png)
ony low frequencies | ![](g/g_modified_spectrum0.png) | ![](g/g_output0.png)
no low frequencies | ![](g/g_modified_spectrum1.png) | ![](g/g_output1.png)
only high frequencies | ![](g/g_modified_spectrum2.png) | ![](g/g_output2.png)
only very high frequencies | ![](g/g_modified_spectrum5.png) | ![](g/g_output5.png)
removed low frequences and high vertical frequences | ![](g/g_modified_spectrum3.png) | ![](g/g_output3.png)
removed low frequences and high horizontal frequences | ![](g/g_modified_spectrum4.png) | ![](g/g_output4.png)
??? | ![](g/g_modified_spectrum6.png) | ![](g/g_output6.png)
??? | ![](g/g_modified_spectrum7.png) | ![](g/g_output7.png)

Alternatively one can also use the Matlab script `prova.m`
