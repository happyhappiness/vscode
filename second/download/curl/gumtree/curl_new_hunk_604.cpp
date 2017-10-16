        nread++;
        ptr++;
      }
    }
    *ptr=0; /* zero terminate */

#if KRB4
    { /* handle the security-oriented responses 6xx ***/
      /* FIXME: some errorchecking perhaps... ***/
      if(strncmp(buf, "631", 3) == 0)
        sec_read_msg(conn, buf, prot_safe);
      else if(strncmp(buf, "632", 3) == 0)
        sec_read_msg(conn, buf, prot_private);
      else if(strncmp(buf, "633", 3) == 0)
        sec_read_msg(conn, buf, prot_confidential);
      nread = strlen(buf);
    }
#endif

    if(data->bits.verbose && buf[0]) {
      fputs("< ", data->err);
      fwrite(buf, 1, nread, data->err);
      fputs("\n", data->err);
    }
  } while(!error &&
