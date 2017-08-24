{
        host->encalloc = (char *)ace_hostname;
        /* change the name pointer to point to the encoded hostname */
        host->name = host->encalloc;
      }