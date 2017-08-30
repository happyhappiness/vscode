      /* if a line like this was already allocated, free the previous one */

      if(conn->allocptr.rangeline)

        free(conn->allocptr.rangeline);

      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", data->reqdata.range);

    }

    else if((httpreq != HTTPREQ_GET) &&

            !checkheaders(data, "Content-Range:")) {



      if(data->reqdata.resume_from) {

        /* This is because "resume" was selected */

        curl_off_t total_expected_size=

          data->reqdata.resume_from + data->set.infilesize;

        conn->allocptr.rangeline =

            aprintf("Content-Range: bytes %s%" FORMAT_OFF_T

                    "/%" FORMAT_OFF_T "\r\n",

                    data->reqdata.range, total_expected_size-1,

                    total_expected_size);

      }

      else {

        /* Range was selected and then we just pass the incoming range and

           append total size */

        conn->allocptr.rangeline =

            aprintf("Content-Range: bytes %s/%" FORMAT_OFF_T "\r\n",

                    data->reqdata.range, data->set.infilesize);

      }

    }

  }

