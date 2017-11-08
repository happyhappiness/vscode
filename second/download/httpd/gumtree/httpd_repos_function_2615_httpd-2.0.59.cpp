static
int isSpace(int c)
{
  switch (c) {
  case 0x20:
  case 0xD:
  case 0xA:
  case 0x9:	
    return 1;
  }
  return 0;
}