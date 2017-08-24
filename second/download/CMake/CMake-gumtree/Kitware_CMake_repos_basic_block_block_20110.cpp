{
  int name_size, is_path_dir;
  DWORD attr, last_error;
  WCHAR* dir = NULL, *dir_to_watch, *pathw = NULL;
  WCHAR short_path_buffer[MAX_PATH];
  WCHAR* short_path;

  if (uv__is_active(handle))
    return UV_EINVAL;

  handle->cb = cb;
  handle->path = uv__strdup(path);
  if (!handle->path) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  uv__handle_start(handle);

  /* Convert name to UTF16. */

  name_size = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0) *
              sizeof(WCHAR);
  pathw = (WCHAR*)uv__malloc(name_size);
  if (!pathw) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  if (!MultiByteToWideChar(CP_UTF8,
                           0,
                           path,
                           -1,
                           pathw,
                           name_size / sizeof(WCHAR))) {
    return uv_translate_sys_error(GetLastError());
  }

  /* Determine whether path is a file or a directory. */
  attr = GetFileAttributesW(pathw);
  if (attr == INVALID_FILE_ATTRIBUTES) {
    last_error = GetLastError();
    goto error;
  }

  is_path_dir = (attr & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;

  if (is_path_dir) {
     /* path is a directory, so that's the directory that we will watch. */
    dir_to_watch = pathw;
  } else {
    /*
     * path is a file.  So we split path into dir & file parts, and
     * watch the dir directory.
     */

    /* Convert to short path. */
    short_path = short_path_buffer;
    if (!GetShortPathNameW(pathw, short_path, ARRAY_SIZE(short_path))) {
      short_path = NULL;
    }

    if (uv_split_path(pathw, &dir, &handle->filew) != 0) {
      last_error = GetLastError();
      goto error;
    }

    if (uv_split_path(short_path, NULL, &handle->short_filew) != 0) {
      last_error = GetLastError();
      goto error;
    }

    dir_to_watch = dir;
    uv__free(pathw);
    pathw = NULL;
  }

  handle->dir_handle = CreateFileW(dir_to_watch,
                                   FILE_LIST_DIRECTORY,
                                   FILE_SHARE_READ | FILE_SHARE_DELETE |
                                     FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_FLAG_BACKUP_SEMANTICS |
                                     FILE_FLAG_OVERLAPPED,
                                   NULL);

  if (dir) {
    uv__free(dir);
    dir = NULL;
  }

  if (handle->dir_handle == INVALID_HANDLE_VALUE) {
    last_error = GetLastError();
    goto error;
  }

  if (CreateIoCompletionPort(handle->dir_handle,
                             handle->loop->iocp,
                             (ULONG_PTR)handle,
                             0) == NULL) {
    last_error = GetLastError();
    goto error;
  }

  if (!handle->buffer) {
    handle->buffer = (char*)uv__malloc(uv_directory_watcher_buffer_size);
  }
  if (!handle->buffer) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  memset(&(handle->req.u.io.overlapped), 0,
         sizeof(handle->req.u.io.overlapped));

  if (!ReadDirectoryChangesW(handle->dir_handle,
                             handle->buffer,
                             uv_directory_watcher_buffer_size,
                             (flags & UV_FS_EVENT_RECURSIVE) ? TRUE : FALSE,
                             FILE_NOTIFY_CHANGE_FILE_NAME      |
                               FILE_NOTIFY_CHANGE_DIR_NAME     |
                               FILE_NOTIFY_CHANGE_ATTRIBUTES   |
                               FILE_NOTIFY_CHANGE_SIZE         |
                               FILE_NOTIFY_CHANGE_LAST_WRITE   |
                               FILE_NOTIFY_CHANGE_LAST_ACCESS  |
                               FILE_NOTIFY_CHANGE_CREATION     |
                               FILE_NOTIFY_CHANGE_SECURITY,
                             NULL,
                             &handle->req.u.io.overlapped,
                             NULL)) {
    last_error = GetLastError();
    goto error;
  }

  assert(is_path_dir ? pathw != NULL : pathw == NULL);
  handle->dirw = pathw;
  handle->req_pending = 1;
  return 0;

error:
  if (handle->path) {
    uv__free(handle->path);
    handle->path = NULL;
  }

  if (handle->filew) {
    uv__free(handle->filew);
    handle->filew = NULL;
  }

  if (handle->short_filew) {
    uv__free(handle->short_filew);
    handle->short_filew = NULL;
  }

  uv__free(pathw);

  if (handle->dir_handle != INVALID_HANDLE_VALUE) {
    CloseHandle(handle->dir_handle);
    handle->dir_handle = INVALID_HANDLE_VALUE;
  }

  if (handle->buffer) {
    uv__free(handle->buffer);
    handle->buffer = NULL;
  }

  if (uv__is_active(handle))
    uv__handle_stop(handle);

  return uv_translate_sys_error(last_error);
}