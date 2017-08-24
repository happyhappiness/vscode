(GetFileType(child_handle)) {
          case FILE_TYPE_DISK:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN;
            break;

          case FILE_TYPE_PIPE:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FPIPE;
            break;

          case FILE_TYPE_CHAR:
          case FILE_TYPE_REMOTE:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
            break;

          case FILE_TYPE_UNKNOWN:
            if (GetLastError() != 0) {
              err = GetLastError();
              CloseHandle(child_handle);
              goto error;
            }
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
            break;

          default:
            assert(0);
            return -1;
        }