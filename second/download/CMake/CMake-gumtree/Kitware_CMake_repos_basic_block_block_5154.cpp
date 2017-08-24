{
      struct Curl_easy *recv_handle = conn->recv_pipe.head->ptr;

      recv_size = recv_handle->req.size;

      if(penalty_size > 0 && recv_size > penalty_size)
        penalized = TRUE;
    }