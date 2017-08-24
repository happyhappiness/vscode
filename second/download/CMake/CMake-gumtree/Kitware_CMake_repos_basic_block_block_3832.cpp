{
        error = EAI_MEMORY;
        free(ca->ai_addr);
        free(ca);
        break;
      }