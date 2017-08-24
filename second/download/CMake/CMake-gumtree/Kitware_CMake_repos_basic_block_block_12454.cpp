(client_offset < rar->dbo[rar->cursor].start_offset &&
          rar->file_flags & FHD_SPLIT_BEFORE)
        {
          /* Search backwards for the correct data block */
          if (rar->cursor == 0)
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Attempt to seek past beginning of RAR data block");
            return (ARCHIVE_FAILED);
          }
          rar->cursor--;
          client_offset -= rar->dbo[rar->cursor+1].start_offset -
            rar->dbo[rar->cursor].end_offset;
          if (client_offset < rar->dbo[rar->cursor].start_offset)
            continue;
          ret = __archive_read_seek(a, rar->dbo[rar->cursor].start_offset -
            rar->dbo[rar->cursor].header_size, SEEK_SET);
          if (ret < (ARCHIVE_OK))
            return ret;
          ret = archive_read_format_rar_read_header(a, a->entry);
          if (ret != (ARCHIVE_OK))
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Error during seek of RAR file");
            return (ARCHIVE_FAILED);
          }
          rar->cursor--;
          break;
        }
        else if (client_offset > rar->dbo[rar->cursor].end_offset &&
          rar->file_flags & FHD_SPLIT_AFTER)
        {
          /* Search forward for the correct data block */
          rar->cursor++;
          if (rar->cursor < rar->nodes &&
            client_offset > rar->dbo[rar->cursor].end_offset)
          {
            client_offset += rar->dbo[rar->cursor].start_offset -
              rar->dbo[rar->cursor-1].end_offset;
            continue;
          }
          rar->cursor--;
          ret = __archive_read_seek(a, rar->dbo[rar->cursor].end_offset,
                                    SEEK_SET);
          if (ret < (ARCHIVE_OK))
            return ret;
          ret = archive_read_format_rar_read_header(a, a->entry);
          if (ret == (ARCHIVE_EOF))
          {
            rar->has_endarc_header = 1;
            ret = archive_read_format_rar_read_header(a, a->entry);
          }
          if (ret != (ARCHIVE_OK))
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Error during seek of RAR file");
            return (ARCHIVE_FAILED);
          }
          client_offset += rar->dbo[rar->cursor].start_offset -
            rar->dbo[rar->cursor-1].end_offset;
          continue;
        }