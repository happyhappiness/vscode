       host due to a location-follow, we do some weirdo checks here */

    if(!data->state.this_is_a_follow ||

       !data->state.auth_host ||

       curl_strequal(data->state.auth_host, conn->hostname)) {

      sprintf(data->state.buffer, "%s:%s",

              data->state.user, data->state.passwd);

      if(Curl_base64_encode(data->state.buffer, strlen(data->state.buffer),

