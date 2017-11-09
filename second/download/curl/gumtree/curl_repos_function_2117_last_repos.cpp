static curl_off_t multipart_size(curl_mime *mime)
{
  curl_off_t size;
  curl_off_t sz;
  size_t boundarysize;
  curl_mimepart *part;

  if(!mime)
    return 0;           /* Not present -> empty. */

  boundarysize = 4 + strlen(mime->boundary) + 2;
  size = boundarysize;  /* Final boundary - CRLF after headers. */

  for(part = mime->firstpart; part; part = part->nextpart) {
    sz = Curl_mime_size(part);

    if(sz < 0)
      size = sz;

    if(size >= 0)
      size += boundarysize + sz;
  }

  return size;
}