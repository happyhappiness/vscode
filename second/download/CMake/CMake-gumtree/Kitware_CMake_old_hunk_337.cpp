    /* As RFC3617 describes the separator slash is not actually part of the

       file name so we skip the always-present first letter of the path

       string. */

    filename = curl_easy_unescape(data, &state->conn->data->state.path[1], 0,

                                  NULL);

    if(!filename)

      return CURLE_OUT_OF_MEMORY;



    snprintf((char *)state->spacket.data+2,

             state->blksize,

