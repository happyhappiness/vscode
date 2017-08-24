(!QueueUserWorkItem(&uv_pipe_writefile_thread_proc,
                           req,
                           WT_EXECUTELONGFUNCTION)) {
      uv_fatal_error(GetLastError(), "QueueUserWorkItem");
    }