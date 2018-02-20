function [result] = BKisOrthonormal( inmat , epsilon )
%This function will test for orthonormality between vectors listed as
%columns in the input argument "inmat". The value "epsilon" is used to
%prevent errors due to floating point precision
%   Detailed explanation goes here
[rows cols] = size(inmat);
for k = 1:cols-1
    for m = k+1:cols
        %fprintf("inmat(:,%d) = \n",k); inmat(:,k)
        %fprintf("inmat(:,%d) = \n",m);  inmat(:,m)
        
        %fprintf("dot:\n"); dot(inmat(:,k),inmat(:,m))
        if dot(inmat(:,k),inmat(:,m)) > epsilon
           result = 0;
           return;
        end
    end
end
result = 1;
end

