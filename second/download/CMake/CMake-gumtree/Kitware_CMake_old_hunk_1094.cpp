            break;

          case 3:

          {

            length = *(p + offset++);

            while (length)

            {

	          if (filename_size >= end)

			    break;

              filename[filename_size++] = *(p + offset);

              length--;

            }

          }

          break;

        }

      }

      if (filename_size >= end) {

        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

          "Invalid filename");

        return (ARCHIVE_FATAL);

