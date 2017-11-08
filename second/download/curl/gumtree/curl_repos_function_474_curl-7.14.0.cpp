static int showit(struct SessionHandle *data, curl_infotype type,
                  char *ptr, size_t size)
{
  static const char * const s_infotype[CURLINFO_END] = {
    "* ", "< ", "> ", "{ ", "} ", "{ ", "} " };

  if(data->set.fdebug)
    return (*data->set.fdebug)(data, type, ptr, size,
                               data->set.debugdata);

  switch(type) {
  case CURLINFO_TEXT:
  case CURLINFO_HEADER_OUT:
  case CURLINFO_HEADER_IN:
    fwrite(s_infotype[type], 2, 1, data->set.err);
    fwrite(ptr, size, 1, data->set.err);
    break;
  default: /* nada */
    break;
  }
  return 0;
}