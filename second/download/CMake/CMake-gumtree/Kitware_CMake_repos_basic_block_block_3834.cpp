f(ai->ai_canonname != NULL) {
      ca->ai_canonname = strdup(ai->ai_canonname);
      if(!ca->ai_canonname) {
        error = EAI_MEMORY;
        free(ca->ai_addr);
        free(ca);
        break;
      }
    }