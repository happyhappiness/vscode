{
      infof(data, "Pipe broke: handle %p, url = %s\n",
            (void *)data, data->state.path);

      if(data->mstate < CURLM_STATE_COMPLETED) {
        /* Head back to the CONNECT state */
        multistate(data, CURLM_STATE_CONNECT);
        rc = CURLM_CALL_MULTI_PERFORM;
        result = CURLE_OK;
      }

      data->state.pipe_broke = FALSE;
      data->easy_conn = NULL;
      continue;
    }