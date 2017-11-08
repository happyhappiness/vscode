static void base64Decode(unsigned char *dest, char *src, int *rawLength)
{
  int length = 0;
  int equalsTerm = 0;
  int i;
  int numQuantums;
  unsigned char lastQuantum[3];
	
  while((src[length] != '=') && src[length])
    length++;
  while(src[length+equalsTerm] == '=')
    equalsTerm++;
  
  numQuantums = (length + equalsTerm) / 4;
  if(rawLength)
    *rawLength = (numQuantums * 3) - equalsTerm;
  
  for(i = 0; i < numQuantums - 1; i++) {
    decodeQuantum(dest, src);
    dest += 3; src += 4;
  }

  decodeQuantum(lastQuantum, src);
  for(i = 0; i < 3 - equalsTerm; i++)
    dest[i] = lastQuantum[i];
	
}