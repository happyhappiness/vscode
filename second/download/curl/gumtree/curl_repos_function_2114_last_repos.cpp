size_t Curl_mime_read(char *buffer, size_t size, size_t nitems, void *instream)
{
  curl_mimepart *part = (curl_mimepart *) instream;

  (void) size;   /* Always 1. */
  return readback_part(part, buffer, nitems);
}