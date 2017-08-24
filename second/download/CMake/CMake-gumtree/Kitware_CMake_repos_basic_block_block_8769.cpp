{
    EVP_DigestFinal(*ctx, md, NULL);
    EVP_MD_CTX_free(*ctx);
    *ctx = NULL;
  }