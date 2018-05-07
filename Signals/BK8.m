clc;
clear all;
close all;

%% Question 2
b = [1 0.4 0.3];
a = [1 -0.9 0.81];
figure;
[z,p,k] = tf2zp(b,a);
zplane(z,p);

%% Question 3
N = 10000;
V = normrnd(0, sqrt(3), 1, N);
X = filter(b,a,V);

%% Question 4
r0 = (X * X.')/N
r1 = (X(1:9999) * X(2:end).')/9999
r2 = (X(1:9998) *  X(3:end).')/9998
r3 = (X(1:9997) * X(4:end).')/9997
r4 = (X(1:9996) * X(5:end).')/9996
r5 = (X(1:9995) * X(6:end).')/9995

%% Question 5
corel = [r0 r1 r2 r3 r4 r5];
corelmat = toeplitz(corel)

%% Question 6
corelmatEig = eig(corelmat)
fprintf('All of the eigenvalues are non-negative real\n');

%% Question 7
[s_est,w] = pwelch(X,hamming(512),256,512);

%% Question 8
s_est = s_est/mean(s_est);
[h,w2] = freqz(b,a,N);
h = abs(h);
h = h.^2;
h = h/mean(h);
figure;
hold on
plot(w2,h);
plot(w,s_est);
ylabel("Margnitude");
xlabel("Digital Radian Frequency");
axis([0 pi 0 12]);
legend('PSD','Pwelch');
hold off;

%% Question 9
fprintf('The angle of the pole of H is %.04d, this is close to 1, as can be seen on the graph.\n', angle(p(1)));

%% Question 10
row = X(5:10000);
col = X(1:6);
A = toeplitz(fliplr(col),row);
singsA = svd(A);
comp = singsA.^2;
comp = comp/9995;
comp = sort(comp)
corelmatEig = sort(corelmatEig);
[U S V] = svd(A);
Eigs = (corelmat*U) ./ U
diff  = sort(mean(Eigs)) - sort(corelmatEig.')
fprintf('The difference between these is very close to 0\n');