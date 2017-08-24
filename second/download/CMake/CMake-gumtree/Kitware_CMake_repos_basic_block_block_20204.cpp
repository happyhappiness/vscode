{
      FILE_DIRECTORY_INFORMATION* info;
      uv__dirent_t* dirent;

      size_t wchar_len;
      size_t utf8_len;

      /* Obtain a pointer to the current directory entry. */
      position += next_entry_offset;
      info = (FILE_DIRECTORY_INFORMATION*) position;

      /* Fetch the offset to the next directory entry. */
      next_entry_offset = info->NextEntryOffset;

      /* Compute the length of the filename in WCHARs. */
      wchar_len = info->FileNameLength / sizeof info->FileName[0];

      /* Skip over '.' and '..' entries.  It has been reported that
       * the SharePoint driver includes the terminating zero byte in
       * the filename length.  Strip those first.
       */
      while (wchar_len > 0 && info->FileName[wchar_len - 1] == L'\0')
        wchar_len -= 1;

      if (wchar_len == 0)
        continue;
      if (wchar_len == 1 && info->FileName[0] == L'.')
        continue;
      if (wchar_len == 2 && info->FileName[0] == L'.' &&
          info->FileName[1] == L'.')
        continue;

      /* Compute the space required to store the filename as UTF-8. */
      utf8_len = WideCharToMultiByte(
          CP_UTF8, 0, &info->FileName[0], wchar_len, NULL, 0, NULL, NULL);
      if (utf8_len == 0)
        goto win32_error;

      /* Resize the dirent array if needed. */
      if (dirents_used >= dirents_size) {
        size_t new_dirents_size =
            dirents_size == 0 ? dirents_initial_size : dirents_size << 1;
        uv__dirent_t** new_dirents =
            uv__realloc(dirents, new_dirents_size * sizeof *dirents);

        if (new_dirents == NULL)
          goto out_of_memory_error;

        dirents_size = new_dirents_size;
        dirents = new_dirents;
      }

      /* Allocate space for the uv dirent structure. The dirent structure
       * includes room for the first character of the filename, but `utf8_len`
       * doesn't count the NULL terminator at this point.
       */
      dirent = uv__malloc(sizeof *dirent + utf8_len);
      if (dirent == NULL)
        goto out_of_memory_error;

      dirents[dirents_used++] = dirent;

      /* Convert file name to UTF-8. */
      if (WideCharToMultiByte(CP_UTF8,
                              0,
                              &info->FileName[0],
                              wchar_len,
                              &dirent->d_name[0],
                              utf8_len,
                              NULL,
                              NULL) == 0)
        goto win32_error;

      /* Add a null terminator to the filename. */
      dirent->d_name[utf8_len] = '\0';

      /* Fill out the type field. */
      if (info->FileAttributes & FILE_ATTRIBUTE_DEVICE)
        dirent->d_type = UV__DT_CHAR;
      else if (info->FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        dirent->d_type = UV__DT_LINK;
      else if (info->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        dirent->d_type = UV__DT_DIR;
      else
        dirent->d_type = UV__DT_FILE;
    }