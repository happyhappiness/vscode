f(socksreq[1] == 255) { /* status / message type */
    failf(data, "User was rejected by the SOCKS5 server (%u %u).",
          (unsigned int)socksreq[0], (unsigned int)socksreq[1]);
    s_pSecFn->DeleteSecurityContext(&sspi_context);
    return CURLE_COULDNT_CONNECT;
  }