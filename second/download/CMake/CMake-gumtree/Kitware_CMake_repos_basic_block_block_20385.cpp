{
          UnregisterWait(handle->read_req.wait_handle);
          handle->read_req.wait_handle = INVALID_HANDLE_VALUE;
        }