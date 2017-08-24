{
      free(certbuf);
      CFRelease(array);
      failf(data, "SSL: invalid CA certificate #%d (offset %d) in bundle",
            n, offset);
      return CURLE_SSL_CACERT;
    }