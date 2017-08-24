f(maj_stat == GSS_S_COMPLETE) {
        if(sizeof(buf) > len + status_string.length)
          strcpy(buf+len, (char *) status_string.value);
        gss_release_buffer(&min_stat, &status_string);
        break;
      }