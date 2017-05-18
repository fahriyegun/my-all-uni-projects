function [ output ] = correlate(T,I)
T1 = T - mean(mean(T));
I1 = I - mean(mean(I));

nT = sqrt(sum (sum(T1.^2)));
nI = sqrt(sum (sum(I1.^2)));

output= sum(sum(T1.*I1))/ (nT.*nI);
end