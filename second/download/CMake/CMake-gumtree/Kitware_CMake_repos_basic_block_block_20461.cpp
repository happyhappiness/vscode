(!req->event_handle) {
          uv_fatal_error(GetLastError(), "CreateEvent");
        }