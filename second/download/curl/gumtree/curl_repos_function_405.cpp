CURLcode Curl_http_done(struct connectdata *conn,
                        CURLcode status)
{
  struct SessionHandle *data;
  struct HTTP *http;

  data=conn->data;
  http=conn->proto.http;

  /* set the proper values (possibly modified on POST) */
  conn->fread = data->set.fread; /* restore */
  conn->fread_in = data->set.in; /* restore */

  if (http == NULL)
    return CURLE_OK;

  if(http->send_buffer) {
    send_buffer *buff = http->send_buffer;

    free(buff->buffer);
    free(buff);
    http->send_buffer = NULL; /* clear the pointer */
  }

  if(HTTPREQ_POST_FORM == data->set.httpreq) {
    conn->bytecount = http->readbytecount + http->writebytecount;

    Curl_formclean(http->sendit); /* Now free that whole lot */
    if(http->form.fp) {
      /* a file being uploaded was left opened, close it! */
      fclose(http->form.fp);
      http->form.fp = NULL;
    }
  }
  else if(HTTPREQ_PUT == data->set.httpreq)
    conn->bytecount = http->readbytecount + http->writebytecount;

  if (status != CURLE_OK)
    return (status);

  if(!conn->bits.retry &&
     ((http->readbytecount +
       conn->headerbytecount -
       conn->deductheadercount)) <= 0) {
    /* If this connection isn't simply closed to be retried, AND nothing was
       read from the HTTP server (that counts), this can't be right so we
       return an error here */
    failf(data, "Empty reply from server");
    return CURLE_GOT_NOTHING;
  }

  return CURLE_OK;
}