    /* As RFC3617 describes the separator slash is not actually part of the

       file name so we skip the always-present first letter of the path

       string. */

    result = Curl_urldecode(data, &state->conn->data->state.path[1], 0,

                            &filename, NULL, FALSE);

    if(result)

      return result;



    snprintf((char *)state->spacket.data+2,

             state->blksize,

