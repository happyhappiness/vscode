    p += filename_size;
  }

  /* Split file in multivolume RAR. No more need to process header. */
  if (rar->filename_save &&
    !memcmp(rar->filename, rar->filename_save, filename_size + 1))
  {
    __archive_read_consume(a, header_size - 7);
    rar->cursor++;
    if (rar->cursor >= rar->nodes)
    {
      rar->nodes++;
      if ((rar->dbo =
        realloc(rar->dbo, sizeof(*rar->dbo) * rar->nodes)) == NULL)
      {
        archive_set_error(&a->archive, ENOMEM, "Couldn't allocate memory.");
        return (ARCHIVE_FATAL);
      }
      rar->dbo[rar->cursor].header_size = header_size;
      rar->dbo[rar->cursor].start_offset = -1;
      rar->dbo[rar->cursor].end_offset = -1;
    }
    if (rar->dbo[rar->cursor].start_offset < 0)
    {
      rar->dbo[rar->cursor].start_offset = a->filter->position;
      rar->dbo[rar->cursor].end_offset = rar->dbo[rar->cursor].start_offset +
        rar->packed_size;
    }
    return ret;
  }

  rar->filename_save = (char*)realloc(rar->filename_save,
                                      filename_size + 1);
  memcpy(rar->filename_save, rar->filename, filename_size + 1);

  /* Set info for seeking */
  free(rar->dbo);
  if ((rar->dbo = calloc(1, sizeof(*rar->dbo))) == NULL)
  {
    archive_set_error(&a->archive, ENOMEM, "Couldn't allocate memory.");
    return (ARCHIVE_FATAL);
  }
  rar->dbo[0].header_size = header_size;
  rar->dbo[0].start_offset = -1;
  rar->dbo[0].end_offset = -1;
  rar->cursor = 0;
  rar->nodes = 1;

  if (rar->file_flags & FHD_SALT)
  {
    if (p + 8 > endp) {
