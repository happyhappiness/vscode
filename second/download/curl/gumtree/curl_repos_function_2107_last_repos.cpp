CURLcode curl_mime_data(curl_mimepart *part,
                        const char *data, size_t datasize)
{
  if(!part)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  cleanup_part_content(part);

  if(data) {
    if(datasize == CURL_ZERO_TERMINATED)
      datasize = strlen(data);

    part->data = malloc(datasize + 1);
    if(!part->data)
      return CURLE_OUT_OF_MEMORY;

    part->datasize = datasize;

    if(datasize)
      memcpy(part->data, data, datasize);
    part->data[datasize] = '\0';    /* Set a nul terminator as sentinel. */

    part->readfunc = mime_mem_read;
    part->seekfunc = mime_mem_seek;
    part->freefunc = mime_mem_free;
    part->kind = MIMEKIND_DATA;
  }

  return CURLE_OK;
}