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

