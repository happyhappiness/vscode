static CURLcode file_or_stdin(curl_mimepart *part, const char *file)
{
  if(strcmp(file, "-"))
    return curl_mime_filedata(part, file);

  return curl_mime_data_cb(part, -1, (curl_read_callback) fread,
                           (curl_seek_callback) fseek, NULL, stdin);
}