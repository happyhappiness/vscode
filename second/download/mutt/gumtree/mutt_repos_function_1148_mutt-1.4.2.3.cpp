static void Decode (output, input, len)
uint32_t *output;
unsigned char *input;
unsigned int len;
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
 output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
   (((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
}