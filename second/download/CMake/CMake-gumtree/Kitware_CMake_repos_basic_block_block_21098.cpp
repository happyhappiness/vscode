(!ReadConsoleInputW(handle->handle,
                             &handle->tty.rd.last_input_record,
                             1,
                             &records_read)) {
        handle->flags &= ~UV_HANDLE_READING;
        DECREASE_ACTIVE_COUNT(loop, handle);
        handle->read_cb((uv_stream_t*) handle,
                        uv_translate_sys_error(GetLastError()),
                        &buf);
        goto out;
      }