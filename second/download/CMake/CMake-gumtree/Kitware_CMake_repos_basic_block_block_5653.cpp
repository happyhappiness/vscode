f(err == SEC_E_ILLEGAL_MESSAGE)
    snprintf(outbuf, outmax,
             "SEC_E_ILLEGAL_MESSAGE (0x%08X) - This error usually occurs "
             "when a fatal SSL/TLS alert is received (e.g. handshake failed). "
             "More detail may be available in the Windows System event log.",
             err)