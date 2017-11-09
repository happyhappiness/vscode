static CURLcode setname(curl_mimepart *part, const char *name, size_t len)
{
  char *zname;
  CURLcode res;

  if(!name || !len)
    return curl_mime_name(part, name);
  zname = malloc(len + 1);
  if(!zname)
    return CURLE_OUT_OF_MEMORY;
  memcpy(zname, name, len);
  zname[len] = '\0';
  res = curl_mime_name(part, zname);
  free(zname);
  return res;
}