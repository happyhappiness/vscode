    return AUTH_ERROR;
  }
  p += 5;
  len = Curl_base64_decode(p, (char *)adat.dat);
  if(len < 0) {
    Curl_failf(data, "Failed to decode base64 from server");
    return AUTH_ERROR;
  }
  adat.length = len;
  ret = krb_rd_safe(adat.dat, adat.length, &d->key,
                    (struct sockaddr_in *)hisctladdr,
