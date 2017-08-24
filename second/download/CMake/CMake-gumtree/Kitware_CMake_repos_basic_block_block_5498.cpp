{
      /* A previous substring matched so output that first */
      memcpy(&scratch[si], &SMTP_EOB[eob_sent], smtp->eob - eob_sent);
      si += smtp->eob - eob_sent;

      /* Then compare the first byte */
      if(SMTP_EOB[0] == data->req.upload_fromhere[i])
        smtp->eob = 1;
      else
        smtp->eob = 0;

      eob_sent = 0;

      /* Reset the trailing CRLF flag as there was more data */
      smtp->trailing_crlf = FALSE;
    }