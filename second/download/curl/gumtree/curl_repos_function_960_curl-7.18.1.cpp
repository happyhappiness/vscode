static CURLcode file_connect(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data = conn->data;
  char *real_path = curl_easy_unescape(data, data->state.path, 0, NULL);
  struct FILEPROTO *file;
  int fd;
#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
  int i;
  char *actual_path;
#endif

  if(!real_path)
    return CURLE_OUT_OF_MEMORY;

  /* If there already is a protocol-specific struct allocated for this
     sessionhandle, deal with it */
  Curl_reset_reqproto(conn);

  if(!data->state.proto.file) {
    file = (struct FILEPROTO *)calloc(sizeof(struct FILEPROTO), 1);
    if(!file) {
      free(real_path);
      return CURLE_OUT_OF_MEMORY;
    }
    data->state.proto.file = file;
  }
  else {
    /* file is not a protocol that can deal with "persistancy" */
    file = data->state.proto.file;
    Curl_safefree(file->freepath);
    if(file->fd != -1)
      close(file->fd);
    file->path = NULL;
    file->freepath = NULL;
    file->fd = -1;
  }

#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
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
      (actual_path[2] == ':' || actual_path[2] == '|'))
  {
    actual_path[2] = ':';
    actual_path++;
  }

  /* change path separators from '/' to '\\' for DOS, Windows and OS/2 */
  for (i=0; actual_path[i] != '\0'; ++i)
    if(actual_path[i] == '/')
      actual_path[i] = '\\';

  fd = open(actual_path, O_RDONLY | O_BINARY);  /* no CR/LF translation! */
  file->path = actual_path;
#else
  fd = open(real_path, O_RDONLY);
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