function [ outmat ] = BKorthoProj(inmat,invector)
%UNTITLED Summary of this function goes here
%   Takes input vector "invector" and space of orthonormal vectors "inmat"
%   and returns the projection of the input vector into the space of the
%   orthonormal vectors
[rows cols] = size(inmat);
outmat = zeros(rows,1);
for k = 1:cols
    outmat = outmat + dot(inmat(:,k),invector)*inmat(:,k);
end

end

