static void base64Decode(unsigned char *dest, char *src, int *rawLength)
{
  int length = 0;
  int equalsTerm = 0;
  int i;
  unsigned char lastQuantum[3];
	
  while((src[length] != '=') && src[length])
    length++;
  while(src[length+equalsTerm] == '=')
    equalsTerm++;
  
  if(rawLength)
    *rawLength = (length * 3 / 4) - equalsTerm;
  
  for(i = 0; i < length/4 - 1; i++) {
    decodeQuantum(dest, src);
    dest += 3; src += 4;
  }

  decodeQuantum(lastQuantum, src);
  for(i = 0; i < 3 - equalsTerm; i++) dest[i] = lastQuantum[i];
	
}