CURLcode Curl_http_done(struct connectdata *conn)
{
  struct SessionHandle *data;
  struct HTTP *http;

  data=conn->data;
  http=conn->proto.http;

  /* set the proper values (possibly modified on POST) */
  conn->fread = data->set.fread; /* restore */
  conn->fread_in = data->set.in; /* restore */

  if(http->send_buffer) {
    send_buffer *buff = http->send_buffer;
    
    free(buff->buffer);
    free(buff);
  }

  if(HTTPREQ_POST_FORM == data->set.httpreq) {
    conn->bytecount = http->readbytecount + http->writebytecount;
      
    Curl_formclean(http->sendit); /* Now free that whole lot */
  }
  else if(HTTPREQ_PUT == data->set.httpreq)
    conn->bytecount = http->readbytecount + http->writebytecount;

  if(0 == (http->readbytecount + conn->headerbytecount)) {
    /* nothing was read from the HTTP server, this can't be right
       so we return an error here */
    failf(data, "Empty reply from server");
    return CURLE_GOT_NOTHING;
  }

  return CURLE_OK;
}