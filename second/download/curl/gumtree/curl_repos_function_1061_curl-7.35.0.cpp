static void MD4Pad(MD4_CTX *context)
{
  unsigned char bits[8];
  unsigned int bufindex, padLen;

  /* Save number of bits */
  Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64.
   */
  bufindex = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (bufindex < 56) ? (56 - bufindex) : (120 - bufindex);
  MD4Update (context, PADDING, padLen);

  /* Append length (before padding) */
  MD4Update (context, bits, 8);
}