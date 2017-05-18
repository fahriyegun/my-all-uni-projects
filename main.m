im=imread('birds2.jpg');%read image and create a matrice
temp=imcrop(im,[175,250,315,210]);
%imshow(temp)
%example coordinates
rs=250;%row start
re=460;%row end
cs=175;%column start
ce=490;%column end
startWithoutLoop=datetime
reverseImageWithoutLoop(im,rs,re,cs,ce);%call reverseImageWithoutLoop function
endWithoutLoop = datetime
runtimeWithoutLoop=endWithoutLoop-startWithoutLoop