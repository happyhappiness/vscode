        localaddr->sin_addr = natAddr;
      }
    }
  }
#endif

  result = Curl_base64_encode(conn->data, (char *)adat.dat, adat.length,
                              &p, &base64_sz);
  if(result) {
    Curl_failf(data, "base64-encoding: %s", curl_easy_strerror(result));
    return AUTH_CONTINUE;
  }

  result = Curl_ftpsendf(conn, "ADAT %s", p);

  free(p);
