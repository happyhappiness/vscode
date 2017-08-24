f(1 > rc) {
        /*
         * We couldn't even get this format.
         * djgpp 2.04 has a sscanf() bug where 'conn->host.name' is
         * assigned, but the return value is EOF!
         */
#if defined(__DJGPP__) && (DJGPP_MINOR == 4)
        if(!(rc == -1 && *conn->host.name))
#endif
        {
          failf(data, "<url> malformed");
          return CURLE_URL_MALFORMAT;
        }
      }