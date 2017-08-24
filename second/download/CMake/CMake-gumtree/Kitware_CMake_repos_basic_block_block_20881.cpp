{
      handle->read_req.event_handle = CreateEvent(NULL, 0, 0, NULL);
      if (!handle->read_req.event_handle) {
        uv_fatal_error(GetLastError(), "CreateEvent");
      }
    }