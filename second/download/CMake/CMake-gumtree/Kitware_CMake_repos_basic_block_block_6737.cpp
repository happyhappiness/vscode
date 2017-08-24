r(i=0; i<NUM_OF_CIPHERS; i++) {
    PRInt32 policy = 0;
    SSL_CipherPolicyGet(cipherlist[i].num, &policy);
    if(policy)
      return TRUE;
  }