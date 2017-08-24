    conn->allocptr.cookie = aprintf("Cookie: %s\015\012", data->set.cookie);
  }

  if(conn->bits.upload_chunky) {
    if(!checkheaders(data, "Transfer-Encoding:")) {
      te = "Transfer-Encoding: chunked\r\n";
    }
    /* else
       our header was already added, what to do now? */
  }

  if(data->cookies) {
    co = Curl_cookie_getlist(data->cookies,
                             host, ppath,
                             (conn->protocol&PROT_HTTPS?TRUE:FALSE));
  }
  if (data->change.proxy && *data->change.proxy &&
      !data->set.tunnel_thru_httpproxy &&
      !(conn->protocol&PROT_HTTPS))  {
    /* The path sent to the proxy is in fact the entire URL */
