CURLcode Curl_file_connect(struct connectdata *conn)
{
  char *actual_path = curl_unescape(conn->path, 0);
  struct FILE *file;
  int fd;
#if defined(WIN32) || defined(__EMX__)
  int i;
#endif

  file = (struct FILE *)malloc(sizeof(struct FILE));
  if(!file)
    return CURLE_OUT_OF_MEMORY;

  memset(file, 0, sizeof(struct FILE));
  conn->proto.file = file;

#if defined(WIN32) || defined(__EMX__)
  /* change path separators from '/' to '\\' for Windows and OS/2 */
  for (i=0; actual_path[i] != '\0'; ++i)
    if (actual_path[i] == '/')
      actual_path[i] = '\\';

  fd = open(actual_path, O_RDONLY | O_BINARY);	/* no CR/LF translation! */
#else
  fd = open(actual_path, O_RDONLY);
#endif
  free(actual_path);

  if(fd == -1) {
    failf(conn->data, "Couldn't open file %s", conn->path);
    return CURLE_FILE_COULDNT_READ_FILE;
  }
  file->fd = fd;

  return CURLE_OK;
}