}
#endif

#ifdef TEST_DECODE
/* decoding test harness. Read in a base64 string from stdin and write out the 
 * length returned by Curl_base64_decode, followed by the decoded data itself
 */
#include <stdio.h>

#define TEST_NEED_SUCK
void *suck(int *);

int main(int argc, char **argv, char **envp)
{
  char *base64;
  int base64Len;
  unsigned char *data;
  int dataLen;
	
  base64 = (char *)suck(&base64Len);
  data = (unsigned char *)malloc(base64Len * 3/4 + 8);
  dataLen = Curl_base64_decode(base64, data);
  
  fprintf(stderr, "%d\n", dataLen);
  fwrite(data,1,dataLen,stdout);
  
  free(base64); free(data);
  return 0;
}
#endif

