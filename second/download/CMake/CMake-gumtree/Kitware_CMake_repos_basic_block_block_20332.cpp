(name_len == 0) {
          req->retcode = uv_translate_sys_error(GetLastError());
          goto complete;
        }