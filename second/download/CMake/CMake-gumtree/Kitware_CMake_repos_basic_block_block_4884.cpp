{
      sigpipe_ignore(multi->closure_handle, &pipe_st);
      restore_pipe = TRUE;

      multi->closure_handle->dns.hostcache = &multi->hostcache;
      Curl_hostcache_clean(multi->closure_handle,
                           multi->closure_handle->dns.hostcache);

      Curl_close(multi->closure_handle);
    }