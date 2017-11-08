static CURLcode
process_zlib_error(struct SessionHandle *data, z_stream *z)
{
  if (z->msg)
    failf (data, "Error while processing content unencoding.\n%s",
           z->msg);
  else
    failf (data, "Error while processing content unencoding.\n"
           "Unknown failure within decompression software.");

  return CURLE_BAD_CONTENT_ENCODING;
}