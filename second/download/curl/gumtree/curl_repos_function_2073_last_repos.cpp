static char *search_header(struct curl_slist *hdrlist, const char *hdr)
{
  size_t len = strlen(hdr);
  char *value = NULL;

  for(; !value && hdrlist; hdrlist = hdrlist->next)
    value = match_header(hdrlist, hdr, len);

  return value;
}