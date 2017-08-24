f(idn2_check_version(IDN2_VERSION)) {
      char *ace_hostname = NULL;
#if IDN2_VERSION_NUMBER >= 0x00140000
      /* IDN2_NFC_INPUT: Normalize input string using normalization form C.
         IDN2_NONTRANSITIONAL: Perform Unicode TR46 non-transitional
         processing. */
      int flags = IDN2_NFC_INPUT | IDN2_NONTRANSITIONAL;
#else
      int flags = IDN2_NFC_INPUT;
#endif
      int rc = idn2_lookup_ul((const char *)host->name, &ace_hostname, flags);
      if(rc == IDN2_OK) {
        host->encalloc = (char *)ace_hostname;
        /* change the name pointer to point to the encoded hostname */
        host->name = host->encalloc;
      }
      else
        infof(data, "Failed to convert %s to ACE; %s\n", host->name,
              idn2_strerror(rc));
    }