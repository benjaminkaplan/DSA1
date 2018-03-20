fprintf('order is %d\n', filtord(b,a));
%fprintf('The filter of order 2*n = %d\n', 2*n);
zplane(z,p);
figure;
%freqz(b,a,1000);
subplot(2,1,1); hold on;
plot(mag2db(abs(H)));
%plot(linspace(0,1,1000),rs);

%plot([0,1000],[-1*rs,-1*rs],'--');

plot([0,1000],[0,0],'--');

stop = mag2db(abs(H))<-1*rs;
stop = stop * -1 *rs;
stop( stop == 0) = NaN;
plot(stop , '--');

pass = mag2db(abs(H)) > -1*rp;
pass = pass *-1*rp;
pass(pass == 0) = NaN;
plot(pass, '--');
hold off;

subplot(2,1,2);
plot(linspace(1,fNyq,1000),rad2deg(angle(H)));
