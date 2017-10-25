CURLcode http_done(struct connectdata *conn)
{
  struct UrlData *data;
  long *bytecount = &conn->bytecount;
  struct HTTP *http;

  data=conn->data;
  http=data->proto.http;

  if(data->bits.http_formpost) {
    *bytecount = http->readbytecount + http->writebytecount;
      
    FormFree(http->sendit); /* Now free that whole lot */

    data->fread = http->storefread; /* restore */
    data->in = http->in; /* restore */
  }
  else if(data->bits.http_put) {
    *bytecount = http->readbytecount + http->writebytecount;
  }

  /* TBD: the HTTP struct remains allocated here */

  return CURLE_OK;
}