    return AUTH_ERROR;
  }
  p += 5;
  len = Curl_base64_decode(p, &ptr);
  if(len > sizeof(adat.dat)-1) {
    free(ptr);
    len=0;
  }
  if(!len || !ptr) {
    Curl_failf(data, "Failed to decode base64 from server");
    return AUTH_ERROR;
  }
  memcpy((char *)adat.dat, ptr, len);
  free(ptr);
  adat.length = len;
  ret = krb_rd_safe(adat.dat, adat.length, &d->key,
                    (struct sockaddr_in *)hisctladdr,
