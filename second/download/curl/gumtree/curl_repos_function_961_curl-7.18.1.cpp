static CURLcode file_done(struct connectdata *conn,
                               CURLcode status, bool premature)
{
  struct FILEPROTO *file = conn->data->state.proto.file;
  (void)status; /* not used */
  (void)premature; /* not used */
  Curl_safefree(file->freepath);

  if(file->fd != -1)
    close(file->fd);

  return CURLE_OK;
}