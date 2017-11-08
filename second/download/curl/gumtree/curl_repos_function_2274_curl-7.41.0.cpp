static int num_enabled_ciphers(void)
{
  PRInt32 policy = 0;
  int count = 0;
  unsigned int i;

  for(i=0; i<NUM_OF_CIPHERS; i++) {
    SSL_CipherPolicyGet(cipherlist[i].num, &policy);
    if(policy)
      count++;
  }
  return count;
}