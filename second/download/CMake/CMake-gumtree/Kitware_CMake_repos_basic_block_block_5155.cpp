{
    bool penalized = FALSE;
    curl_off_t penalty_size =
      Curl_multi_content_length_penalty_size(data->multi);
    curl_off_t chunk_penalty_size =
      Curl_multi_chunk_length_penalty_size(data->multi);
    curl_off_t recv_size = -2; /* Make it easy to spot in the log */

    /* Find the head of the recv pipe, if any */
    if(conn->recv_pipe.head) {
      struct Curl_easy *recv_handle = conn->recv_pipe.head->ptr;

      recv_size = recv_handle->req.size;

      if(penalty_size > 0 && recv_size > penalty_size)
        penalized = TRUE;
    }

    if(chunk_penalty_size > 0 &&
       (curl_off_t)conn->chunk.datasize > chunk_penalty_size)
      penalized = TRUE;

    infof(data, "Conn: %ld (%p) Receive pipe weight: (%"
          CURL_FORMAT_CURL_OFF_T "/%zu), penalized: %s\n",
          conn->connection_id, (void *)conn, recv_size,
          conn->chunk.datasize, penalized?"TRUE":"FALSE");
    return penalized;
  }