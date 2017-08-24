(((rar->mode) & AE_IFMT) == AE_IFLNK)
  {
    /* Make sure a symbolic-link file does not have its body. */
    rar->bytes_remaining = 0;
    archive_entry_set_size(entry, 0);

    /* Read a symbolic-link name. */
    if ((ret2 = read_symlink_stored(a, entry, sconv)) < (ARCHIVE_WARN))
      return ret2;
    if (ret > ret2)
      ret = ret2;
  }