      /* only read more data if there's no upload data already

         present in the upload buffer */

      if(0 == conn->upload_present) {

        /* init the "upload from here" pointer */

        conn->upload_fromhere = k->uploadbuf;



        nread = data->set.fread(conn->upload_fromhere, 1,

                                BUFSIZE, data->set.in);



        /* the signed int typecase of nread of for systems that has

           unsigned size_t */

