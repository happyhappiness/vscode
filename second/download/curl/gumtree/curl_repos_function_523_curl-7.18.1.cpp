static CURLcode
process_zlib_error(struct connectdata *conn, z_stream *z)
{
  struct SessionHandle *data = conn->data;
  if(z->msg)
    failf (data, "Error while processing content unencoding: %s",
           z->msg);
  else
    failf (data, "Error while processing content unencoding: "
           "Unknown failure within decompression software.");

  return CURLE_BAD_CONTENT_ENCODING;
}