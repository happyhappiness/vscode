{
            infof(data, "CONNECT responded chunked\n");
            chunked_encoding = TRUE;
            /* init our chunky engine */
            Curl_httpchunk_init(conn);
          }