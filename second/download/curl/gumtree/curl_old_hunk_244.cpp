      if(len > (int)WARN_TEXTWIDTH) {
        int cut = WARN_TEXTWIDTH-1;

        while(!ISSPACE(ptr[cut]) && cut) {
          cut--;
        }

        fwrite(ptr, cut + 1, 1, config->errors);
        fputs("\n", config->errors);
        ptr += cut+1; /* skip the space too */
        len -= cut;
      }
