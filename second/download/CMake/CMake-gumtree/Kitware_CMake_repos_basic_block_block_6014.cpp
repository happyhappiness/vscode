{
        /* Match the last part of the name to the domain we are checking. */
        const char *checkn = name + namelen - (tok_end - tok_start);
        if(strncasecompare(no_proxy + tok_start, checkn,
                           tok_end - tok_start)) {
          if((tok_end - tok_start) == namelen || *(checkn - 1) == '.') {
            /* We either have an exact match, or the previous character is a .
             * so it is within the same domain, so no proxy for this host.
             */
            return TRUE;
          }
        }
      }