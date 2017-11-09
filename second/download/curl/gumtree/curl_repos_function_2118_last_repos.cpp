curl_off_t Curl_mime_size(curl_mimepart *part)
{
  curl_off_t size;

  if(part->datasize < 0 && part->kind == MIMEKIND_MULTIPART)
    part->datasize = multipart_size(part->arg);

  size = part->datasize;

  if(part->encoder)
    size = part->encoder->sizefunc(part);

  if(size >= 0 && !(part->flags & MIME_BODY_ONLY)) {
    /* Compute total part size. */
    size += slist_size(part->curlheaders, 2, NULL);
    size += slist_size(part->userheaders, 2, "Content-Type");
    size += 2;    /* CRLF after headers. */
  }
  return size;
}