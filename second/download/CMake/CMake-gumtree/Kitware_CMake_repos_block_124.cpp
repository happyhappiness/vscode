{
      q = curl_maprintf("%lu", len);
      if(q) {
        Curl_ssl_push_certinfo(data, certnum, "RSA Public Key", q);
        free((char *) q);
      }
    }