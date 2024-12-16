% Load the image
img = imread('palace.jpg'); % Replace 'image.png' with your image file

% Convert to grayscale if the image is RGB
if size(img, 3) == 3
    img = rgb2gray(img);
end

% Compute the 2D Fourier Transform
F = fft2(double(img));

% Shift zero-frequency component to the center
F_shifted = fftshift(F);

% Compute the magnitude spectrum
magnitude_spectrum = log(1 + abs(F_shifted));

% Display the original image
subplot(1, 2, 1);
imshow(img, []);
title('Original Image');

% Display the magnitude spectrum
subplot(1, 2, 2);
imshow(magnitude_spectrum, []);
title('Magnitude Spectrum');
