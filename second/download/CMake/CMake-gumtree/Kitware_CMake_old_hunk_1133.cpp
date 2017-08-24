#else
        char *ip = (char *)inet_ntoa(natAddr);
#endif
        Curl_infof(data, "Using NAT IP address (%s) for kerberos 4\n", ip);
        localaddr->sin_addr = natAddr;
      }
    }
  }
#endif

  if(Curl_base64_encode((char *)adat.dat, adat.length, &p) < 1) {
    Curl_failf(data, "Out of memory base64-encoding");
    return AUTH_CONTINUE;
  }
