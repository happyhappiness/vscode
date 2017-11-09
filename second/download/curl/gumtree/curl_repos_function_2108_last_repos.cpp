CURLcode curl_mime_filedata(curl_mimepart *part, const char *filename)
{
  CURLcode result = CURLE_OK;
  char *base;

  if(!part)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  cleanup_part_content(part);

  if(filename) {
    struct_stat sbuf;

    if(stat(filename, &sbuf) || access(filename, R_OK))
      result = CURLE_READ_ERROR;

    part->data = strdup(filename);
    if(!part->data)
      result = CURLE_OUT_OF_MEMORY;

    part->datasize = -1;
    if(!result && S_ISREG(sbuf.st_mode)) {
      part->datasize = filesize(filename, sbuf);
      part->seekfunc = mime_file_seek;
    }

    part->readfunc = mime_file_read;
    part->freefunc = mime_file_free;
    part->kind = MIMEKIND_FILE;

    /* As a side effect, set the filename to the current file's base name.
       It is possible to withdraw this by explicitly calling
       curl_mime_filename() with a NULL filename argument after the current
       call. */
    base = strippath(filename);
    if(!base)
      result = CURLE_OUT_OF_MEMORY;
    else {
      CURLcode res = curl_mime_filename(part, base);

      if(res)
        result = res;
      free(base);
    }
  }
  return result;
}