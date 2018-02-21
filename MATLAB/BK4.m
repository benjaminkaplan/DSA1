clc;
clear all;

%% More Elements in each vector than the number of vectors
C = [rand([10 1]) rand([10 1]) rand([10 1])];
D = BKgramSchmidt(C);
answer = BKisOrthonormal(D, 10*eps());
K = BKorthoProj(D, rand([10 1]));



%% Number of elements = Number of vectors
for z = 1:10
    C(:,z) = rand([10 1]);
end
D = BKgramSchmidt(C);
answer = BKisOrthonormal(D, 100*eps());
K = BKorthoProj(D, rand([10 1]));

%% Next Section
F = linspace(0,2*pi, 1000);
E = sin(F);
L = zeros(length(F),5);
for x = 1:5
    L(:,x) = (1/(sqrt(2*pi)))*exp(-(E-((x-1)*pi/2)).^2); 
end
figure; hold on;
title('Graph of sin(x) and gaussian distributions of sin(x)');
xlabel('0<x<2\pi');
ylabel('sin(x) and guassian distributions');

plot(F, E);
plot(F, L(:,1));
plot(F, L(:,2));
plot(F, L(:,3));
plot(F, L(:,4));
plot(F, L(:,5));
legend('sin(x)', '\mu = 0', '\mu = ^{\pi}/_{2}', '\mu = \pi', '\mu = ^{3\pi}/_{2}', 'mu = 2\pi');
hold off;

H = BKgramSchmidt(L);
BKisOrthonormal(H, 1); 
%The error here is enormous because I am doing Gram-Schmidt on a 1000
%dimensional vector, so I just used 1 as the "fudge factor"
M = BKorthoProj(H, E);
figure;
subplot(2,1,1);
title('Graph of sin(x) and estimated sin(x) using Gram-Schmidt');
xlabel('0<x<2\pi');
ylabel('sin(x) and Gram-Schmidt estimate of sin(x)');
hold on 
plot(F,E);
plot(F,M);
hold off;
subplot(2,1,2);
title('Orthonormal Basis Functions');
xlabel('0<x<2\pi');
ylabel('Orth. Basis Functions');
hold on;
plot(F,H(:,1));
plot(F,H(:,2));
plot(F,H(:,3));
plot(F,H(:,4));
plot(F,H(:,5));
hold off;