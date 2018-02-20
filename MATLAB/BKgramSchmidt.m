function [outmat] = BKgramSchmidt( inmat )
%BKgramSchmidt Does the Gram Schmidt algorithm
%   returns orthonormal set of vectors from input vectors
[rows cols] = size(inmat);
outmat = zeros(rows, cols);
%outmat = zeros(size(inmat,1),length(inmat));
outmat(:,1) = inmat(:,1) ./ norm(inmat(:,1));
subtractors = zeros(rows,1);
for k = 2:cols
    for m = 1 : k-1 %forms projection of each vector onto the previous orthonormal ones
        %fprintf("k = %d | m = %d\n", k,m); %diagnostic tool to tell what
        %level you are at 
        dot(inmat(:,k), outmat(:,m));
        subtractors = subtractors + dot(inmat(:,k), outmat(:,m)).*outmat(:,m);
    end
    outmat(:,k) = inmat(:,k) - subtractors;
    outmat(:,k) = outmat(:,k) ./ norm(outmat(:,k)); %normalizes newest vector in outmat
end 

end

