        localaddr->sin_addr = natAddr;
      }
    }
  }
#endif

  if(Curl_base64_encode(conn->data, (char *)adat.dat, adat.length, &p) < 1) {
    Curl_failf(data, "Out of memory base64-encoding");
    return AUTH_CONTINUE;
  }

  result = Curl_ftpsendf(conn, "ADAT %s", p);

  free(p);
