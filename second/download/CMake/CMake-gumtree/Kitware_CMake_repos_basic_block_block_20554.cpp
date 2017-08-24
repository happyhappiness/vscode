{
  NTSTATUS nt_status;
  IO_STATUS_BLOCK io_status;
  FILE_NAME_INFORMATION tmp_name_info;
  FILE_NAME_INFORMATION* name_info;
  WCHAR* name_buf;
  unsigned int addrlen;
  unsigned int name_size;
  unsigned int name_len;
  int err;

  name_info = NULL;

  if (handle->handle == INVALID_HANDLE_VALUE) {
    *size = 0;
    return UV_EINVAL;
  }

  uv__pipe_pause_read((uv_pipe_t*)handle); /* cast away const warning */

  nt_status = pNtQueryInformationFile(handle->handle,
                                      &io_status,
                                      &tmp_name_info,
                                      sizeof tmp_name_info,
                                      FileNameInformation);
  if (nt_status == STATUS_BUFFER_OVERFLOW) {
    name_size = sizeof(*name_info) + tmp_name_info.FileNameLength;
    name_info = uv__malloc(name_size);
    if (!name_info) {
      *size = 0;
      err = UV_ENOMEM;
      goto cleanup;
    }

    nt_status = pNtQueryInformationFile(handle->handle,
                                        &io_status,
                                        name_info,
                                        name_size,
                                        FileNameInformation);
  }

  if (nt_status != STATUS_SUCCESS) {
    *size = 0;
    err = uv_translate_sys_error(pRtlNtStatusToDosError(nt_status));
    goto error;
  }

  if (!name_info) {
    /* the struct on stack was used */
    name_buf = tmp_name_info.FileName;
    name_len = tmp_name_info.FileNameLength;
  } else {
    name_buf = name_info->FileName;
    name_len = name_info->FileNameLength;
  }

  if (name_len == 0) {
    *size = 0;
    err = 0;
    goto error;
  }

  name_len /= sizeof(WCHAR);

  /* check how much space we need */
  addrlen = WideCharToMultiByte(CP_UTF8,
                                0,
                                name_buf,
                                name_len,
                                NULL,
                                0,
                                NULL,
                                NULL);
  if (!addrlen) {
    *size = 0;
    err = uv_translate_sys_error(GetLastError());
    goto error;
  } else if (pipe_prefix_len + addrlen >= *size) {
    /* "\\\\.\\pipe" + name */
    *size = pipe_prefix_len + addrlen + 1;
    err = UV_ENOBUFS;
    goto error;
  }

  memcpy(buffer, pipe_prefix, pipe_prefix_len);
  addrlen = WideCharToMultiByte(CP_UTF8,
                                0,
                                name_buf,
                                name_len,
                                buffer+pipe_prefix_len,
                                *size-pipe_prefix_len,
                                NULL,
                                NULL);
  if (!addrlen) {
    *size = 0;
    err = uv_translate_sys_error(GetLastError());
    goto error;
  }

  addrlen += pipe_prefix_len;
  *size = addrlen;
  buffer[addrlen] = '\0';

  err = 0;

error:
  uv__free(name_info);

cleanup:
  uv__pipe_unpause_read((uv_pipe_t*)handle); /* cast away const warning */
  return err;
}