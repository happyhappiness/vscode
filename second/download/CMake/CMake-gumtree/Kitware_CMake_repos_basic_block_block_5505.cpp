e(!msg_ctx) {
      /* convert minor status code (underlying routine error) to text */
      maj_stat = gss_display_status(&min_stat, minor_status,
                                    GSS_C_MECH_CODE,
                                    GSS_C_NULL_OID,
                                    &msg_ctx, &status_string);
      if(maj_stat == GSS_S_COMPLETE) {
        if(sizeof(buf) > len + status_string.length)
          strcpy(buf+len, (char *) status_string.value);
        gss_release_buffer(&min_stat, &status_string);
        break;
      }
      gss_release_buffer(&min_stat, &status_string);
    }