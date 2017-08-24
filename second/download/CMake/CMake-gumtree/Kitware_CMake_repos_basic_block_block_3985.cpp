r(i=0; i < count; i++) {
      /* even if one function returns error, this loops through and frees all
         buffers */
      if(!result)
        result = Curl_client_chop_write(data->easy_conn,
                                        writebuf[i].type,
                                        writebuf[i].buf,
                                        writebuf[i].len);
      free(writebuf[i].buf);
    }