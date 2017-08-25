int Curl_base64_encode(const void *inp, int insize, char **outptr)
{
  unsigned char ibuf[3];
  unsigned char obuf[4];
  int i;
  int inputparts;
  char *output;
  char *base64data;

  char *indata = (char *)inp;

  if(0 == insize)
    insize = (int)strlen(indata);

  base64data = output = (char*)malloc(insize*4/3+4);
  if(NULL == output)
    return -1;

  while(insize > 0) {
    for (i = inputparts = 0; i < 3; i++) { 
      if(*indata) {
        inputparts++;
        ibuf[i] = *indata;
        indata++;
        insize--;
      }
      else
        ibuf[i] = 0;
    }
                       
    obuf [0] = (unsigned char)((ibuf [0] & 0xFC) >> 2);
    obuf [1] = (unsigned char)(((ibuf [0] & 0x03) << 4) | 
                               ((ibuf [1] & 0xF0) >> 4));
    obuf [2] = (unsigned char)(((ibuf [1] & 0x0F) << 2) | 
                               ((ibuf [2] & 0xC0) >> 6));
    obuf [3] = (unsigned char)(ibuf [2] & 0x3F);

    switch(inputparts) {
    case 1: /* only one byte read */
      sprintf(output, "%c%c==", 
              table64[obuf[0]],
              table64[obuf[1]]);
      break;
    case 2: /* two bytes read */
      sprintf(output, "%c%c%c=", 
              table64[obuf[0]],
              table64[obuf[1]],
              table64[obuf[2]]);
      break;
    default:
      sprintf(output, "%c%c%c%c", 
              table64[obuf[0]],
              table64[obuf[1]],
              table64[obuf[2]],
              table64[obuf[3]] );
      break;
    }
    output += 4;
  }
  *output=0;
  *outptr = base64data; /* make it return the actual data memory */

  return (int)strlen(base64data); /* return the length of the new data */
}