f(socksreq[1] != 2) { /* status / message type */
    failf(data, "Invalid SSPI encryption response type (%u %u).",
          (unsigned int)socksreq[0], (unsigned int)socksreq[1]);
    s_pSecFn->DeleteSecurityContext(&sspi_context);
    return CURLE_COULDNT_CONNECT;
  }