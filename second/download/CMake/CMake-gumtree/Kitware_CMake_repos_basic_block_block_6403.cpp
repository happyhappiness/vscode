f(!*outptr || !*outlen) {
    free(*outptr);
    return CURLE_REMOTE_ACCESS_DENIED;
  }