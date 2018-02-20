clc;
clear all;
A = [ 1 2 3; 4 5 6 ; 7 8 9; 10 11 12];
B = BKgramSchmidt(A);
answer = BKisOrthonormal(B,10*eps())
C = [rand([10 1]) rand([10 1]) rand([10 1])]
D = BKgramSchmidt(C);
answer = BKisOrthonormal(D, 10*eps())
F = linspace(0,2*pi, 1000);
E = sin(F);
one = (1/(sqrt(2*pi)))*exp(-(E-0).^2);
two = (1/(sqrt(2*pi)))*exp(-(E-(pi/2)).^2);
three = (1/(sqrt(2*pi)))*exp(-(E-pi).^2);
four = (1/(sqrt(2*pi)))*exp(-(E-(3*pi/2)).^2);
five = (1/(sqrt(2*pi)))*exp(-(E-(2*pi)).^2);
figure; hold on;
title('Graph of sin(x) and gaussian distributions of sin(x)');
xlabel('0<x<2\pi');
ylabel('sin(x) and guassian distributions');

plot(F, E);
plot(F, one);
plot(F, two);
plot(F, three);
plot(F, four);
plot(F, five);
legend('sin(x)', '\mu = 0', '\mu = ^{\pi}/_{2}', '\mu = \pi', '\mu = ^{3\pi}/_{2}', 'mu = 2\pi');
hold off;
G = [one.', two.', three.', four.', five.'];
H = BKgramSchmidt(G);
BKisOrthonormal(H, 10*eps())