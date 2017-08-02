{
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Attempt to seek past beginning of RAR data block");
            return (ARCHIVE_FAILED);
          }