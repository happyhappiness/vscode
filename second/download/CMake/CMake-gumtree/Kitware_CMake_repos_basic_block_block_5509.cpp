{
      /* convert major status code (GSS-API error) to text */
      maj_stat = gss_display_status(&min_stat, major_status,
                                    GSS_C_GSS_CODE,
                                    GSS_C_NULL_OID,
                                    &msg_ctx, &status_string);
      if(maj_stat == GSS_S_COMPLETE) {
        if(sizeof(buf) > len + status_string.length + 1) {
          strcpy(buf+len, (char *) status_string.value);
          len += status_string.length;
        }
        gss_release_buffer(&min_stat, &status_string);
        break;
      }
      gss_release_buffer(&min_stat, &status_string);
    }