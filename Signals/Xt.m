function [ output ] = Xt( input )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
[rows cols] = size(input);
f0 = 20e6; % 20MHz
fprintf('cols = %d\n',cols);
input
output = ones([rows cols]);
%output = vpa(exp(-1 * input/(0.2e-6)).*cos(2* pi * f0 * input),1000);
for k = 1:cols
    output(k) = vpa(exp(-1 * input(k)/(0.2e-6))*cos(2* pi * f0 * input(k)),100);
end 
end

