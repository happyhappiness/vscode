static size_t read_part_content(curl_mimepart *part,
                                char *buffer, size_t bufsize)
{
  size_t sz = 0;

  if(part->readfunc)
    sz = part->readfunc(buffer, 1, bufsize, part->arg);
  return sz;
}