#include <stdio.h>
#include <stdlib.h>

int main(){

  FILE *img;
  img = fopen("Images/lena512.bmp", "rb"); // open the FILE
  if(img == NULL){
    fprintf(stderr, "Error loading the image\n");
    exit(0);
  }

  //Creating storage for image header and colorTable
  unsigned char header[54];
  unsigned char colorTable[1024];


  //read the first 54 bytes : image header
  int i;
  for(i = 0; i < 54; i++ ){
    header[i] = getc(img);
  }

  //Getting the important information from image header
  // width byte 18, height byte 22 , bitDepth byte 28

  int width = *(int*)&header[18];
  int heigth = *(int*)&header[22];
  int bitDepth = *(int*)&header[28];

  printf("width : %d, heigth : %d, bitDepth : %d \n", width, heigth, bitDepth);

  //Checking if colorTable is needed i.e bitDepth <= 8
  if(bitDepth <= 8){
    fread(colorTable, sizeof(unsigned char), 1024, img);
  }

  //Reading image pixels and storing them in img_pix, size width * heigth
  unsigned char img_pix[width * heigth];
  fread(img_pix, sizeof(unsigned char), (width * heigth), img);

  //Copying img_pix into output img
  //header first then colorTable and finally image pixels
  FILE *img_out = fopen("Images/output_image.bmp", "wb");
  fwrite(header, sizeof(unsigned char), 54, img_out);

  if(bitDepth <= 8){
    fwrite(colorTable, sizeof(unsigned char), 1024, img_out);
  }

  fwrite(img_pix, sizeof(unsigned char), (width * heigth), img_out);

  fclose(img_out);
  fclose(img);

  return 0;
}
