       curl_strequal(data->state.auth_host, conn->hostname)) {

      sprintf(data->state.buffer, "%s:%s",

              data->state.user, data->state.passwd);

      if(Curl_base64_encode(data->state.buffer, strlen(data->state.buffer),

                            &authorization) >= 0) {

        if(conn->allocptr.userpwd)

          free(conn->allocptr.userpwd);

