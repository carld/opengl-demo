/*
 * an 8x8 pixel bitmap font and helper functions
 *
 * font_to_pixels turns the embedded font into a bitmap.
 * font_to_bmp renders the bitmap font to a bmp file using lib SDL.
 * str_to_pixels renders a string to a bitmap using the font.
 *
 * copyright (c) 2010  A. Carl Douglas
 */

#include <stdio.h>

#include <SDL.h>

const char * filename = "font.bmp";

const unsigned charpixw = 8;
const unsigned charpixh = 8;
const unsigned nchars = 8 * 10;

char * fnt1 =

  "        " "    oo  " "  oo oo " "        " "  ooooo " "oooooooo" "oooooooo" "    oo  "
  "        " "    oo  " "  oo oo " " oo  oo " " oo o oo" "oooooooo" "oooooooo" "    oo  "
  "        " "    oo  " "        " "oooooooo" " oo o   " "oooooooo" "oooooooo" "    oo  "
  "        " "    oo  " "        " " oo  oo " "  ooooo " "oooooooo" "oooooooo" "        "
  "        " "        " "        " "oooooooo" "    o oo" "oooooooo" "oooooooo" "        "
  "        " "    oo  " "        " " oo  oo " " oo o oo" "oooooooo" "oooooooo" "        "
  "        " "    oo  " "        " "        " "  ooooo " "oooooooo" "oooooooo" "        "
  "        " "        " "        " "        " "    o   " "        " "        " "        "
  "   ooo  " "   ooo  " "        " "        " "        " "        " "        " "      oo"
  "  oo    " "     oo " "oo oo oo" "   oo   " "        " "        " "        " "     oo "
  " oo     " "      oo" "  oooo  " "   oo   " "        " "        " "        " "    oo  "
  " oo     " "      oo" "oooooooo" " oooooo " "        " " oooooo " "        " "   oo   "
  " oo     " "      oo" "  oooo  " "   oo   " "        " "        " "        " "  oo    "
  "  oo    " "     oo " "oo oo oo" "   oo   " "    oo  " "        " "    oo  " " oo     "
  "   ooo  " "    oo  " "        " "        " "    oo  " "        " "    oo  " "        "
  "        " "        " "        " "        " "   oo   " "        " "        " "        "
  "  ooooo " "    oo  " "  ooooo " "  ooooo " " oo   oo" " ooooooo" "  ooooo " " ooooooo"
  " oo   oo" "   ooo  " " oo   oo" " oo   oo" " oo   oo" " oo     " " oo   oo" "      oo"
  " oo  ooo" "    oo  " "      oo" "      oo" " oo   oo" " oo     " " oo     " "     oo "
  " oo o oo" "    oo  " "     oo " "     oo " " ooooooo" " oooooo " " oooooo " "    oo  "
  " ooo  oo" "    oo  " "    oo  " "      oo" "      oo" "      oo" " oo   oo" "    oo  "
  " oo   oo" "    oo  " "   oo   " " oo   oo" "      oo" " oo   oo" " oo   oo" "    oo  "
  "  ooooo " "  oooooo" " ooooooo" "  ooooo " "      oo" "  ooooo " "  ooooo " "    oo  "
  "        " "        " "        " "        " "        " "        " "        " "        "
  "  ooooo " "  ooooo " "        " "        " "        " "        " "        " "  ooooo "
  " oo   oo" " oo   oo" "   oo   " "   oo   " "   oo   " "        " "    oo  " " oo   oo"
  " oo   oo" " oo   oo" "   oo   " "   oo   " "  oo    " " oooooo " "     oo " "      oo"
  "  ooooo " "  oooooo" "        " "        " " oo     " "        " "      oo" "     oo "
  " oo   oo" "      oo" "   oo   " "   oo   " "  oo    " " oooooo " "     oo " "        "
  " oo   oo" "      oo" "   oo   " "   oo   " "   oo   " "        " "    oo  " "    oo  "
  "  ooooo " "      oo" "        " "  oo    " "        " "        " "        " "    oo  "
  "        " "        " "        " "        " "        " "        " "        " "        "
  "  ooooo " "  ooooo " " ooooo  " "  ooooo " " ooooo  " " ooooooo" " ooooooo" "  ooooo "
  " oo   oo" " oo   oo" " oo  oo " " oo   oo" " oo  oo " " oo     " " oo     " " oo   oo"
  " oo oooo" " oo   oo" " oo   oo" " oo     " " oo   oo" " oo     " " oo     " " oo     "
  " oo oooo" " ooooooo" " oooooo " " oo     " " oo   oo" " oooooo " " oooooo " " oo     "
  " oo oooo" " oo   oo" " oo   oo" " oo     " " oo   oo" " oo     " " oo     " " oo  ooo"
  " oo oooo" " oo   oo" " oo   oo" " oo   oo" " oo   oo" " oo     " " oo     " " oo   oo"
  "  oooooo" " oo   oo" " oooooo " "  ooooo " " oooooo " " ooooooo" " oo     " "  ooooo "
  "        " "        " "        " "        " "        " "        " "        " "        "
  " oo   oo" "  oooooo" " ooooooo" " oo   oo" " oo     " " oo   oo" " oo   oo" "  ooooo "
  " oo   oo" "    oo  " "     oo " " oo  oo " " oo     " " ooo ooo" " ooo  oo" " oo   oo"
  " oo   oo" "    oo  " "     oo " " oo oo  " " oo     " " ooooooo" " oooo oo" " oo   oo"
  " ooooooo" "    oo  " "     oo " " oooo   " " oo     " " oo o oo" " oo oooo" " oo   oo"
  " oo   oo" "    oo  " "     oo " " oo oo  " " oo     " " oo   oo" " oo  ooo" " oo   oo"
  " oo   oo" "    oo  " " oo  oo " " oo  oo " " oo     " " oo   oo" " oo   oo" " oo   oo"
  " oo   oo" "  oooooo" "  oooo  " " oo   oo" " ooooooo" " oo   oo" " oo   oo" "  ooooo "
  "        " "        " "        " "        " "        " "        " "        " "        "
  " oooooo " "  ooooo " " ooooo  " "  ooooo " " ooooooo" " oo   oo" " oo   oo" " oo   oo"
  " oo   oo" " oo   oo" " oo  oo " " oo   oo" "    oo  " " oo   oo" " oo   oo" " oo   oo"
  " oo   oo" " oo   oo" " oo   oo" " oo     " "    oo  " " oo   oo" " oo   oo" " oo o oo"
  " oooooo " " oo   oo" " oooooo " "  ooooo " "    oo  " " oo   oo" " oo   oo" " oo o oo"
  " oo     " " oo oooo" " oo   oo" "      oo" "    oo  " " oo   oo" "  ooooo " " ooooooo"
  " oo     " " oo  ooo" " oo   oo" " oo   oo" "    oo  " "  oo  oo" "   ooo  " " ooo ooo"
  " oo     " "  oooooo" " oo   oo" "  ooooo " "    oo  " "   oooo " "    o   " " oo   oo"
  "        " "        " "        " "        " "        " "        " "        " "        "
  " oo   oo" " oo   oo" " ooooooo" "  oooo  " " oo     " "  oooo  " "oooooooo" "        "
  " oo   oo" " oo   oo" "     oo " "  oo    " "  oo    " "    oo  " "oooooooo" "        "
  "  oo oo " "  oo  oo" "    oo  " "  oo    " "   oo   " "    oo  " "oooooooo" "        "
  "   ooo  " "   ooooo" "   oo   " "  oo    " "    oo  " "    oo  " "oooooooo" "        "
  "  oo oo " "      oo" "  oo    " "  oo    " "     oo " "    oo  " "oooooooo" "        "
  " oo   oo" " oo   oo" " oo     " "  oo    " "      oo" "    oo  " "oooooooo" "        "
  " oo   oo" "  ooooo " " ooooooo" "  oooo  " "        " "  oooo  " "oooooooo" " ooooooo"
  "        " "        " "        " "        " "        " "        " "        " "        "
  " oo   oo" " oo   oo" " ooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  " oo   oo" " oo   oo" "     oo " "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "  oo oo " "  oo  oo" "    oo  " "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "   ooo  " "   ooooo" "   oo   " "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "  oo oo " "      oo" "  oo    " "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  " oo   oo" " oo   oo" " oo     " "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  " oo   oo" "  ooooo " " ooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "        " "        " "        " "        " "        " "        " "        " "        "
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo" "oooooooo"
  "        " "        " "        " "        " "        " "        " "        " "        "
  ;

unsigned char fontpixels[(8*8)*(8*10)];

void font_to_bmp(const char *filename) {
  SDL_Surface *surf;
  surf = SDL_CreateRGBSurfaceFrom(fontpixels, (8*8*10), (8), 8, (8*8*10) * 1, 0xff, 0xff, 0xff, 0);
  if (surf==NULL) { printf("could not create surface?\n"); }
  SDL_SaveBMP(surf, filename);
  SDL_FreeSurface(surf);
  printf("converted ascii font to bitmap\n");
}

void font_to_pixels() {
  unsigned int x,y;
  unsigned int i;
  unsigned int k,j;

  for(i=0;i<64;i++){
    x = (i % 8) * 8; 
    y = (i / 8) * (8 * 8 * 8);

    for (j=0;j<8;j++){
      for(k=0;k<8;k++){
	fontpixels[(i*8)+(j*8*8*10)+k] = 
          (fnt1[(y)+(j*8*8)+(x+k)] == ' ' ? 0x00 : 0xff);
      }
    }
  }
#if 1
  font_to_bmp(filename);
#endif
}

void font_to_data() {
  /* make hex c code array from the data */
}

void str_to_pixels(char *str, unsigned char *pixels, unsigned int width, unsigned int height) {
  int i,j,k;
  for(i=0; *str ; str++,i++) {
    int ch = *str - 0x20;
    for(j=0;j<8;j++) {
      for(k=0;k<8;k++) {
        pixels[(i*8)+(j*width)+(k)] = 
          fontpixels[(ch*8)+(j*8*8*10)+k];
      }
    }
  }
}

