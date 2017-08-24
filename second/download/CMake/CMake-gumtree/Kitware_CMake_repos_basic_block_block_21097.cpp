(handle->tty.rd.last_input_record.EventType == WINDOW_BUFFER_SIZE_EVENT) {
        CONSOLE_SCREEN_BUFFER_INFO info;

        uv_sem_wait(&uv_tty_output_lock);

        if (uv_tty_output_handle != INVALID_HANDLE_VALUE &&
            GetConsoleScreenBufferInfo(uv_tty_output_handle, &info)) {
          uv_tty_update_virtual_window(&info);
        }

        uv_sem_post(&uv_tty_output_lock);

        continue;
      }