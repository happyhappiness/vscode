            break;

          case 3:

          {

            char extra, high;

            uint8_t length = *(p + offset++);



            if (length & 0x80) {

              extra = *(p + offset++);

              high = (char)highbyte;

            } else

              extra = high = 0;

            length = (length & 0x7f) + 2;

            while (length && filename_size < fn_end) {

              unsigned cp = filename_size >> 1;

              filename[filename_size++] = high;

              filename[filename_size++] = p[cp] + extra;

              length--;

            }

          }

          break;

        }

      }

      if (filename_size > fn_end) {

        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

          "Invalid filename");

        return (ARCHIVE_FATAL);

