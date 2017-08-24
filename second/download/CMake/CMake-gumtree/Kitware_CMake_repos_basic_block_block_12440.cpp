(rar->main_flags & MHD_VOLUME && rar->file_flags & FHD_SPLIT_AFTER)
  {
    ret = archive_read_format_rar_read_header(a, a->entry);
    if (ret == (ARCHIVE_EOF))
      ret = archive_read_format_rar_read_header(a, a->entry);
    if (ret != (ARCHIVE_OK))
      return ret;
    return archive_read_format_rar_read_data_skip(a);
  }