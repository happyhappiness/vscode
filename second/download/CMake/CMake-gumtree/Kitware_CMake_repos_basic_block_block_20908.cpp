{
          /* Ouch! serious error. */
          handle->flags &= ~UV_HANDLE_READING;
          DECREASE_ACTIVE_COUNT(loop, handle);

          if (err == WSAECONNABORTED) {
            /* Turn WSAECONNABORTED into UV_ECONNRESET to be consistent with */
            /* Unix. */
            err = WSAECONNRESET;
          }

          handle->read_cb((uv_stream_t*)handle,
                          uv_translate_sys_error(err),
                          &buf);
        }