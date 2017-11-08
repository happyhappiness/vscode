CURLcode Curl_smtp_escape_eob(struct connectdata *conn, ssize_t nread)
{
  /* When sending a SMTP payload we must detect CRLF. sequences making sure
     they are sent as CRLF.. instead, as a . on the beginning of a line will
     be deleted by the server when not part of an EOB terminator and a
     genuine CRLF.CRLF which isn't escaped will wrongly be detected as end of
     data by the server
  */
  ssize_t i;
  ssize_t si;
  struct SessionHandle *data = conn->data;
  struct SMTP *smtp = data->req.protop;

  /* Do we need to allocate the scatch buffer? */
  if(!data->state.scratch) {
    data->state.scratch = malloc(2 * BUFSIZE);

    if(!data->state.scratch) {
      failf (data, "Failed to alloc scratch buffer!");
      return CURLE_OUT_OF_MEMORY;
    }
  }

  /* This loop can be improved by some kind of Boyer-Moore style of
     approach but that is saved for later... */
  for(i = 0, si = 0; i < nread; i++) {
    if(SMTP_EOB[smtp->eob] == data->req.upload_fromhere[i]) {
      smtp->eob++;

      /* Is the EOB potentially the terminating CRLF? */
      if(2 == smtp->eob || SMTP_EOB_LEN == smtp->eob)
        smtp->trailing_crlf = TRUE;
      else
        smtp->trailing_crlf = FALSE;
    }
    else if(smtp->eob) {
      /* A previous substring matched so output that first */
      memcpy(&data->state.scratch[si], SMTP_EOB, smtp->eob);
      si += smtp->eob;

      /* Then compare the first byte */
      if(SMTP_EOB[0] == data->req.upload_fromhere[i])
        smtp->eob = 1;
      else
        smtp->eob = 0;

      /* Reset the trailing CRLF flag as there was more data */
      smtp->trailing_crlf = FALSE;
    }

    /* Do we have a match for CRLF. as per RFC-5321, sect. 4.5.2 */
    if(SMTP_EOB_FIND_LEN == smtp->eob) {
      /* Copy the replacement data to the target buffer */
      memcpy(&data->state.scratch[si], SMTP_EOB_REPL, SMTP_EOB_REPL_LEN);
      si += SMTP_EOB_REPL_LEN;
      smtp->eob = 0;
    }
    else if(!smtp->eob)
      data->state.scratch[si++] = data->req.upload_fromhere[i];
  }

  if(smtp->eob) {
    /* A substring matched before processing ended so output that now */
    memcpy(&data->state.scratch[si], SMTP_EOB, smtp->eob);
    si += smtp->eob;
    smtp->eob = 0;
  }

  if(si != nread) {
    /* Only use the new buffer if we replaced something */
    nread = si;

    /* Upload from the new (replaced) buffer instead */
    data->req.upload_fromhere = data->state.scratch;

    /* Set the new amount too */
    data->req.upload_present = nread;
  }

  return CURLE_OK;
}