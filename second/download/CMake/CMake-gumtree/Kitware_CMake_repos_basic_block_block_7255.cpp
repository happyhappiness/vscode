{
    /* Determine the file's size */
    if(fseek(fp, 0, SEEK_END))
      break;
    filesize = ftell(fp);
    if(fseek(fp, 0, SEEK_SET))
      break;
    if(filesize < 0 || filesize > MAX_PINNED_PUBKEY_SIZE)
      break;

    /*
     * if the size of our certificate is bigger than the file
     * size then it can't match
     */
    size = curlx_sotouz((curl_off_t) filesize);
    if(pubkeylen > size)
      break;

    /*
     * Allocate buffer for the pinned key
     * With 1 additional byte for null terminator in case of PEM key
     */
    buf = malloc(size + 1);
    if(!buf)
      break;

    /* Returns number of elements read, which should be 1 */
    if((int) fread(buf, size, 1, fp) != 1)
      break;

    /* If the sizes are the same, it can't be base64 encoded, must be der */
    if(pubkeylen == size) {
      if(!memcmp(pubkey, buf, pubkeylen))
        result = CURLE_OK;
      break;
    }

    /*
     * Otherwise we will assume it's PEM and try to decode it
     * after placing null terminator
     */
    buf[size] = '\0';
    pem_read = pubkey_pem_to_der((const char *)buf, &pem_ptr, &pem_len);
    /* if it wasn't read successfully, exit */
    if(pem_read)
      break;

    /*
     * if the size of our certificate doesn't match the size of
     * the decoded file, they can't be the same, otherwise compare
     */
    if(pubkeylen == pem_len && !memcmp(pubkey, pem_ptr, pubkeylen))
      result = CURLE_OK;
  }