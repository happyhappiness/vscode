{
  static const size_t dirents_initial_size = 32;

  HANDLE dir_handle = INVALID_HANDLE_VALUE;

  uv__dirent_t** dirents = NULL;
  size_t dirents_size = 0;
  size_t dirents_used = 0;

  IO_STATUS_BLOCK iosb;
  NTSTATUS status;

  /* Buffer to hold directory entries returned by NtQueryDirectoryFile.
   * It's important that this buffer can hold at least one entry, regardless
   * of the length of the file names present in the enumerated directory.
   * A file name is at most 256 WCHARs long.
   * According to MSDN, the buffer must be aligned at an 8-byte boundary.
   */
#if _MSC_VER
  __declspec(align(8)) char buffer[8192];
#else
  __attribute__ ((aligned (8))) char buffer[8192];
#endif

  STATIC_ASSERT(sizeof buffer >=
                sizeof(FILE_DIRECTORY_INFORMATION) + 256 * sizeof(WCHAR));

  /* Open the directory. */
  dir_handle =
      CreateFileW(req->file.pathw,
                  FILE_LIST_DIRECTORY | SYNCHRONIZE,
                  FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                  NULL,
                  OPEN_EXISTING,
                  FILE_FLAG_BACKUP_SEMANTICS,
                  NULL);
  if (dir_handle == INVALID_HANDLE_VALUE)
    goto win32_error;

  /* Read the first chunk. */
  status = pNtQueryDirectoryFile(dir_handle,
                                 NULL,
                                 NULL,
                                 NULL,
                                 &iosb,
                                 &buffer,
                                 sizeof buffer,
                                 FileDirectoryInformation,
                                 FALSE,
                                 NULL,
                                 TRUE);

  /* If the handle is not a directory, we'll get STATUS_INVALID_PARAMETER.
   * This should be reported back as UV_ENOTDIR.
   */
  if (status == STATUS_INVALID_PARAMETER)
    goto not_a_directory_error;

  while (NT_SUCCESS(status)) {
    char* position = buffer;
    size_t next_entry_offset = 0;

    do {
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
    } while (next_entry_offset != 0);

    /* Read the next chunk. */
    status = pNtQueryDirectoryFile(dir_handle,
                                   NULL,
                                   NULL,
                                   NULL,
                                   &iosb,
                                   &buffer,
                                   sizeof buffer,
                                   FileDirectoryInformation,
                                   FALSE,
                                   NULL,
                                   FALSE);

    /* After the first pNtQueryDirectoryFile call, the function may return
     * STATUS_SUCCESS even if the buffer was too small to hold at least one
     * directory entry.
     */
    if (status == STATUS_SUCCESS && iosb.Information == 0)
      status = STATUS_BUFFER_OVERFLOW;
  }

  if (status != STATUS_NO_MORE_FILES)
    goto nt_error;

  CloseHandle(dir_handle);

  /* Store the result in the request object. */
  req->ptr = dirents;
  if (dirents != NULL)
    req->flags |= UV_FS_FREE_PTR;

  SET_REQ_RESULT(req, dirents_used);

  /* `nbufs` will be used as index by uv_fs_scandir_next. */
  req->fs.info.nbufs = 0;

  return;

nt_error:
  SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(status));
  goto cleanup;

win32_error:
  SET_REQ_WIN32_ERROR(req, GetLastError());
  goto cleanup;

not_a_directory_error:
  SET_REQ_UV_ERROR(req, UV_ENOTDIR, ERROR_DIRECTORY);
  goto cleanup;

out_of_memory_error:
  SET_REQ_UV_ERROR(req, UV_ENOMEM, ERROR_OUTOFMEMORY);
  goto cleanup;

cleanup:
  if (dir_handle != INVALID_HANDLE_VALUE)
    CloseHandle(dir_handle);
  while (dirents_used > 0)
    uv__free(dirents[--dirents_used]);
  if (dirents != NULL)
    uv__free(dirents);
}