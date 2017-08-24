{
            /* We either have an exact match, or the previous character is a .
             * so it is within the same domain, so no proxy for this host.
             */
            return TRUE;
          }