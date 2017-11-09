static size_t mime_mem_read(char *buffer, size_t size, size_t nitems,
                            void *instream)
{
  curl_mimepart *part = (curl_mimepart *) instream;
  size_t sz = (size_t) part->datasize - part->state.offset;

  (void) size;   /* Always 1.*/

  if(sz > nitems)
    sz = nitems;

  if(sz)
    memcpy(buffer, (char *) part->data, sz);

  part->state.offset += sz;
  return sz;
}