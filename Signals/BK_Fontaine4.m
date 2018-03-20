%% Benjamin Kaplan - Problem Set IV
close all;

%% Analog Filter
fprintf('Order of analog filter is %d\n', filtord(b,a));
zplane(z,p);
figure;
subplot(2,1,1); hold on;
plot(mag2db(abs(H)));
stop = mag2db(abs(H))<-1*rs;
stop = stop * -1 *rs;
stop( stop == 0) = NaN;
plot(stop , '--');
pass = mag2db(abs(H)) > -1*rp;
pass = pass *-1*rp;
pass(pass == 0) = NaN;
plot(pass, '--');
zerodb = zeros([1 1000]);
TF = isnan(pass);
zerodb(TF) = NaN;
plot(zerodb, '--');
hold off;
subplot(2,1,2);
plot(linspace(1,fNyq,1000),rad2deg(angle(H)));

%% Digital Filter
fprintf('Order of digital filter is %d\n', filtord(bd, ad));
figure;
zplane(zd,pd);
figure;
subplot(2,1,1);
hold on;
plot(mag2db(abs(Hd)));
stop = mag2db(abs(Hd))<-1*rs;
stop = stop * -1 *rs;
stop( stop == 0) = NaN;
plot(stop , '--');
pass = mag2db(abs(Hd)) > -1*rp;
pass = pass *-1*rp;
pass(pass == 0) = NaN;
plot(pass, '--');
zerodb = zeros([1 1000]);
TF = isnan(pass);
zerodb(TF) = NaN;
plot(zerodb, '--');
hold off;
subplot(2,1,2);
plot(linspace(1,fNyq,1000),rad2deg(angle(Hd)));

%% Question 6
z6 = [0.8*exp(j*pi/6) ; 0.8*exp(-j*pi/6) ];
p6 = [ 0.9*exp(j * 3 * pi / 4) ; 0.9*exp(-j * 3 * pi / 4) ];
k6 = 1;
[b6 , a6] = zp2tf(z6,p6,k6);
[h6,t6] = impz(b6,a6);
figure;
stem(t6,h6);
fNyq6 = (150e6)/2;
[freqresp,angresp] = freqz(b,a,linspace(0,fNyq6,1000));
figure;
subplot(2,1,1);
plot(mag2db(abs(freqresp)));
subplot(2,1,2);
plot(rad2deg(angle(freqresp)));

X = Xt(0:50)
Y = filter(b6,a6,X);
figure;
subplot(2,1,1);

stem(X); title('X[n] Discrete');
subplot(2,1,2);
stem(Y); title('Y[n] Discrete');
figure;
subplot(2,1,1);

plot(X);
title('X(t) continuous');
subplot(2,1,2);
plot(Y);
title('Y(t) Continuous');



