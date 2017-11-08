static void MD4Final (unsigned char digest[16], MD4_CTX *context)
{
  /* Do padding */
  MD4Pad (context);

  /* Store state in digest */
  Encode (digest, context->state, 16);

  /* Zeroize sensitive information.
   */
  memset(context, 0, sizeof(*context));
}