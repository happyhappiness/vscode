static CURLcode file_connect(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data = conn->data;
  char *real_path;
  struct FILEPROTO *file = data->req.protop;
  int fd;
#ifdef DOS_FILESYSTEM
  int i;
  char *actual_path;
#endif
  int real_path_len;

  real_path = curl_easy_unescape(data, data->state.path, 0, &real_path_len);
  if(!real_path)
    return CURLE_OUT_OF_MEMORY;

#ifdef DOS_FILESYSTEM
  /* If the first character is a slash, and there's
     something that looks like a drive at the beginning of
     the path, skip the slash.  If we remove the initial
     slash in all cases, paths without drive letters end up
     relative to the current directory which isn't how
     browsers work.

     Some browsers accept | instead of : as the drive letter
     separator, so we do too.

     On other platforms, we need the slash to indicate an
     absolute pathname.  On Windows, absolute paths start
     with a drive letter.
  */
  actual_path = real_path;
  if((actual_path[0] == '/') &&
      actual_path[1] &&
     (actual_path[2] == ':' || actual_path[2] == '|')) {
    actual_path[2] = ':';
    actual_path++;
    real_path_len--;
  }

  /* change path separators from '/' to '\\' for DOS, Windows and OS/2 */
  for(i=0; i < real_path_len; ++i)
    if(actual_path[i] == '/')
      actual_path[i] = '\\';
    else if(!actual_path[i]) /* binary zero */
      return CURLE_URL_MALFORMAT;

  fd = open_readonly(actual_path, O_RDONLY|O_BINARY);
  file->path = actual_path;
#else
  if(memchr(real_path, 0, real_path_len))
    /* binary zeroes indicate foul play */
    return CURLE_URL_MALFORMAT;

  fd = open_readonly(real_path, O_RDONLY);
  file->path = real_path;
#endif
  file->freepath = real_path; /* free this when done */

  file->fd = fd;
  if(!data->set.upload && (fd == -1)) {
    failf(data, "Couldn't open file %s", data->state.path);
    file_done(conn, CURLE_FILE_COULDNT_READ_FILE, FALSE);
    return CURLE_FILE_COULDNT_READ_FILE;
  }
  *done = TRUE;

  return CURLE_OK;
}