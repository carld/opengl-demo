/* test program for bitfont.c */

#include <stdio.h>

void font_to_pixels();
void str_to_pixels(char *, unsigned char *, unsigned int);

int main(int argc, char*argv[])
{
  unsigned char bitmap [8 * 64];
  char *str = "HELLO WORLD";
  font_to_pixels();
  str_to_pixels(str, bitmap, 8);
  return 0;
}

