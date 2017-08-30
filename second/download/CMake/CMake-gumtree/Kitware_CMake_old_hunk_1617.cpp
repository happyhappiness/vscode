int main(int argc, char **argv, char **envp)
{
  char *base64;
  int base64Len;
  unsigned char *data;
  int dataLen;
        
  data = (unsigned char *)suck(&dataLen);
  base64Len = Curl_base64_encode(data, dataLen, &base64);

  fprintf(stderr, "%d\n", base64Len);
  fprintf(stdout, "%s",   base64);
  
  free(base64); free(data);
  return 0;
}
#endif

#ifdef TEST_DECODE
/* decoding test harness. Read in a base64 string from stdin and write out the 
 * length returned by Curl_base64_decode, followed by the decoded data itself
 */
#include <stdio.h>

