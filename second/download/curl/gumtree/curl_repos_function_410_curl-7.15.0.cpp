static void MD5_Update (struct md5_ctx *context,    /* context */
                        const unsigned char *input, /* input block */
                        unsigned int inputLen)      /* length of input block */
{
  unsigned int i, bufindex, partLen;

  /* Compute number of bytes mod 64 */
  bufindex = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3))
      < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);
  
  partLen = 64 - bufindex;

  /* Transform as many times as possible. */
  if (inputLen >= partLen) {
    memcpy((void *)&context->buffer[bufindex], (void *)input, partLen);
    MD5Transform(context->state, context->buffer);
    
    for (i = partLen; i + 63 < inputLen; i += 64)
      MD5Transform(context->state, &input[i]);
    
    bufindex = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  memcpy((void *)&context->buffer[bufindex], (void *)&input[i], inputLen-i);
}