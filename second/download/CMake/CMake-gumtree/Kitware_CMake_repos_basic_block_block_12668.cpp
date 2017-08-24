(*avail == 0 && rar->main_flags & MHD_VOLUME &&
      rar->file_flags & FHD_SPLIT_AFTER)
    {
      ret = archive_read_format_rar_read_header(a, a->entry);
      if (ret == (ARCHIVE_EOF))
      {
        rar->has_endarc_header = 1;
        ret = archive_read_format_rar_read_header(a, a->entry);
      }
      if (ret != (ARCHIVE_OK))
        return NULL;
      return rar_read_ahead(a, min, avail);
    }