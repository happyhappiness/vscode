static void MD4Update(MD4_CTX *context, const unsigned char *input,
                      unsigned int inputLen)
{
  unsigned int i, bufindex, partLen;

  /* Compute number of bytes mod 64 */
  bufindex = (unsigned int)((context->count[0] >> 3) & 0x3F);
  /* Update number of bits */
  if((context->count[0] += ((UINT4)inputLen << 3))
     < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - bufindex;
  /* Transform as many times as possible.
   */
  if(inputLen >= partLen) {
    memcpy(&context->buffer[bufindex], input, partLen);
    MD4Transform (context->state, context->buffer);

    for(i = partLen; i + 63 < inputLen; i += 64)
      MD4Transform (context->state, &input[i]);

    bufindex = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  memcpy(&context->buffer[bufindex], &input[i], inputLen-i);
}