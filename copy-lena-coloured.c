#include <stdio.h>
#include <stdlib.h>

int main(){
    /*
    The goal of this program is to copy a coloured image after opening it and
    reading the headers and colour color table
    */

    FILE * img;
    img = fopen("Images/lena_color.bmp", "rb");
    if(img == NULL){
        fprintf(stderr, "Error loading the file\n");
        exit(0);
    }

    //extracting header and colorTable
    unsigned char header[54];
    unsigned char colorTable[1024];

    for(int i = 0; i < 54; i++){
        header[i] = getc(img);
    }

    int width, height, bitDepth;
    width = *(int*)&header[18];
    height = *(int*)&header[22];
    bitDepth = *(int*)&header[28];

    printf("width : %d, height : %d, bitDepth : %d \n", width, height, bitDepth);

    if(bitDepth <= 8){
        fread(colorTable, sizeof(unsigned char), 1024, img);
    }

    //Copying into new file
    FILE *img_out;
    img_out = fopen("Images/copy_lena_color.bmp", "wb");
    if(img_out == NULL){
        fprintf(stderr, "Error creating new file\n");
        exit(0);
    }

    fwrite(header, sizeof(unsigned char), 54, img_out);
    if(bitDepth <= 8){
        fwrite(colorTable, sizeof(unsigned char), 1024, img_out);
    }

    //extracting image pixels
    unsigned char img_pix[width * height][3];
    unsigned char pix[width * height];
    for(int i = 0; i < width * height; i++){
        img_pix[i][2] = getc(img);
        img_pix[i][1] = getc(img);
        img_pix[i][0] = getc(img);

        putc(img_pix[i][2], img_out);
        putc(img_pix[i][1], img_out);
        putc(img_pix[i][0], img_out);
    }

    fclose(img_out);
    fclose(img);

    printf("End of program\n");
    return 0;
}
