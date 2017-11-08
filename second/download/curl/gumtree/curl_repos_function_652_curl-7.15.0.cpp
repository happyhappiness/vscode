CURLcode Curl_file_done(struct connectdata *conn,
                        CURLcode status)
{
  struct FILEPROTO *file = conn->proto.file;
  (void)status; /* not used */
  Curl_safefree(file->freepath);

  if(file->fd != -1)
    close(file->fd);

  return CURLE_OK;
}