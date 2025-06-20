% Load the image
img = imread('palace/palace.png');

% Convert to grayscale if the image is RGB
if size(img, 3) == 3
    img = rgb2gray(img);
end

% Compute the 2D Fourier Transform
F = fft2(double(img));

% Compute the magnitude spectrum
magnitude_spectrum = log(1 + abs(fftshift(F)));

% Display the original image
subplot(1, 2, 1);
imshow(img, []);
title('Original Image');

% Display the magnitude spectrum
subplot(1, 2, 2);
imshow(magnitude_spectrum, []);
title('Magnitude Spectrum');
