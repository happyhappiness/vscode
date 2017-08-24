    conn->allocptr.cookie = aprintf("Cookie: %s\015\012", data->set.cookie);
  }

  if(!conn->bits.upload_chunky && (data->set.httpreq != HTTPREQ_GET)) {
    /* not a chunky transfer but data is to be sent */
    char *ptr = checkheaders(data, "Transfer-Encoding:");
    if(ptr) {
      /* Some kind of TE is requested, check if 'chunked' is chosen */
      if(Curl_compareheader(ptr, "Transfer-Encoding:", "chunked"))
        /* we have been told explicitly to upload chunky so deal with it! */
        conn->bits.upload_chunky = TRUE;
    }
  }

  if(conn->bits.upload_chunky) {
    /* RFC2616 section 4.4:
       Messages MUST NOT include both a Content-Length header field and a
       non-identity transfer-coding. If the message does include a non-
       identity transfer-coding, the Content-Length MUST be ignored. */

    if(!checkheaders(data, "Transfer-Encoding:")) {
      te = "Transfer-Encoding: chunked\r\n";
    }
    else {
      /* The "Transfer-Encoding:" header was already added. */
      te = "";
    }
  }

  if(data->cookies) {
