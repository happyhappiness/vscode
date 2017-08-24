f(rc == IDN2_OK) {
        host->encalloc = (char *)ace_hostname;
        /* change the name pointer to point to the encoded hostname */
        host->name = host->encalloc;
      }
      else
        infof(data, "Failed to convert %s to ACE; %s\n", host->name,
              idn2_strerror(rc))