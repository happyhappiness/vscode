(handle->flags & UV_HANDLE_EMULATE_IOCP &&
        !handle->read_req.event_handle) {
      handle->read_req.event_handle = CreateEvent(NULL, 0, 0, NULL);
      if (!handle->read_req.event_handle) {
        uv_fatal_error(GetLastError(), "CreateEvent");
      }
    }