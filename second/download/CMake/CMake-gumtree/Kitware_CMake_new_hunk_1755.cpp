      /* only read more data if there's no upload data already

         present in the upload buffer */

      if(0 == conn->upload_present) {

        size_t buffersize = BUFSIZE;

        /* init the "upload from here" pointer */

        conn->upload_fromhere = k->uploadbuf;



        if(!k->upload_done) {



          if(conn->bits.upload_chunky) {

            /* if chunked Transfer-Encoding */

            buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */

            conn->upload_fromhere += 10; /* 32bit hex + CRLF */

          }



          nread = data->set.fread(conn->upload_fromhere, 1,

                                  buffersize, data->set.in);

          

          if(conn->bits.upload_chunky) {

            /* if chunked Transfer-Encoding */

            char hexbuffer[9];

            int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),

                                  "%x\r\n", nread);

            /* move buffer pointer */

            conn->upload_fromhere -= hexlen;

            nread += hexlen;



            /* copy the prefix to the buffer */

            memcpy(conn->upload_fromhere, hexbuffer, hexlen);

            if(nread>0) {

              /* append CRLF to the data */

              memcpy(conn->upload_fromhere +

                     nread, "\r\n", 2);

              nread+=2;

            }

            else {

              /* mark this as done once this chunk is transfered */

              k->upload_done = TRUE;

            }

          }

        }

        else

          nread = 0; /* we're done uploading/reading */



        /* the signed int typecase of nread of for systems that has

           unsigned size_t */

