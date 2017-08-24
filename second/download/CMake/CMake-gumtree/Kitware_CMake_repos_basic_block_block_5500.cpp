{
      smtp->eob++;

      /* Is the EOB potentially the terminating CRLF? */
      if(2 == smtp->eob || SMTP_EOB_LEN == smtp->eob)
        smtp->trailing_crlf = TRUE;
      else
        smtp->trailing_crlf = FALSE;
    }