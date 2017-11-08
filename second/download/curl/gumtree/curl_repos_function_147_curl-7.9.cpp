CURLcode Curl_http_done(struct connectdata *conn)
{
  struct SessionHandle *data;
  long *bytecount = &conn->bytecount;
  struct HTTP *http;

  data=conn->data;
  http=conn->proto.http;

  if(HTTPREQ_POST_FORM == data->set.httpreq) {
    *bytecount = http->readbytecount + http->writebytecount;
      
    Curl_formclean(http->sendit); /* Now free that whole lot */

    data->set.fread = http->storefread; /* restore */
    data->set.in = http->in; /* restore */
  }
  else if(HTTPREQ_PUT == data->set.httpreq) {
    *bytecount = http->readbytecount + http->writebytecount;
  }

  return CURLE_OK;
}