(handle->read_req.event_handle) {
          CloseHandle(handle->read_req.event_handle);
          handle->read_req.event_handle = NULL;
        }