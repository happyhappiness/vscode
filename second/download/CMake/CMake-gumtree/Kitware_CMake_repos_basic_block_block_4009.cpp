{
    /* copy the key */
    memcpy(he->key, key, key_len);
    he->key_len = key_len;
    he->ptr = (void *) p;
  }