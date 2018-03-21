%Benjamin Kaplan - Assignment VI
%% Question 1
clc;
clear all;
close all;
numerator = [(1/2) (2/3) (3/2) 0];
denom = [2 (1/3) 0 (1/2)];
zplane(numerator, denom);
[resp t] = impz(numerator, denom, 50);
figure;
plot(resp);
title('First 50 points of Impulse Response');
xlabel('Points'); ylabel('Impulse Response');
X = ones([1 100]);
for k = 1:100
    X(k) = (-3/4)^(k-1);
end 
Y = filter(numerator, denom, X);
figure;
plot(Y);
title('Filter response of (-3/4)^n');
xlabel('n'); ylabel('Filter Response');
figure;
Z  = conv(resp, X);
plot(Z);
title('Using Convolution in Place of Filter');
xlabel('n'); ylabel('Convolution of Impulse Reponse and Input');

%% Questions 2
fib = ones([1 100]);
for k = 3 : 100
   fib(k) = fib(k-1) +fib(k-2); 
end
figure;
plot(fib);
title('First 100 Values of Fibonacci Sequence');
xlabel('n'); ylabel('Fibonacci Number');
figure;
semilogy(fib);
title('First 100 Values of Fibonacci Sequence Plotted on Logarthmic Scale');
xlabel('n'); ylabel('Fibonacci Number (log)');
output = conv(fib,X); %This is based on the convolution of the impluse response being the same as a filter
figure;
plot(output);
title('X = (-3/4)^n Filtered Using Fibonacci Sequence as Impulse Reponse');
xlabel('n'); ylabel('Filtered Response');
