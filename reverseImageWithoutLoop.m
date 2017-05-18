function [im_wLoop] = reverseImageWithoutLoop (im, rowstart, rowend, colstart,colend)

temp=imcrop(im,[colstart,rowstart,(colend-colstart),(rowend-rowstart)]);%finded bird's coordinates crop 
temp = imrotate(temp,180);%rotate temp picture 180 angle clockwise
im(rowstart:rowend,colstart:colend,:)=temp;%copy from temp array to orginal image
im_wLoop=im;%move from input image to output image
imwrite(im_wLoop,'reversedWithoutLoop.jpg');%save output image 
imshow(im_wLoop) %show output image


end