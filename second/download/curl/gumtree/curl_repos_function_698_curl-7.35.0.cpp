static int check_content_type(const char *content_type, const char *media_type)
{
  const char *ptr = content_type;
  size_t media_type_len = strlen(media_type);
  for(; *ptr && (*ptr == ' ' || *ptr == '\t'); ++ptr);
  if(!*ptr) {
    return 0;
  }
  return Curl_raw_nequal(ptr, media_type, media_type_len) &&
    (*(ptr+media_type_len) == '\0' || *(ptr+media_type_len) == ' ' ||
     *(ptr+media_type_len) == '\t' || *(ptr+media_type_len) == ';');
}