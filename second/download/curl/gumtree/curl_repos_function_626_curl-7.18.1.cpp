int curl_formget(struct curl_httppost *form, void *arg,
                 curl_formget_callback append)
{
  CURLcode rc;
  curl_off_t size;
  struct FormData *data, *ptr;

  rc = Curl_getFormData(&data, form, NULL, &size);
  if(rc != CURLE_OK)
    return (int)rc;

  for (ptr = data; ptr; ptr = ptr->next) {
    if(ptr->type == FORM_FILE) {
      char buffer[8192];
      size_t nread;
      struct Form temp;

      Curl_FormInit(&temp, ptr);

      do {
        nread = readfromfile(&temp, buffer, sizeof(buffer));
        if((nread == (size_t) -1) || (nread != append(arg, buffer, nread))) {
          if(temp.fp) {
            fclose(temp.fp);
          }
          Curl_formclean(&data);
          return -1;
        }
      } while(nread == sizeof(buffer));
    } else {
      if(ptr->length != append(arg, ptr->line, ptr->length)) {
        Curl_formclean(&data);
        return -1;
      }
    }
  }
  Curl_formclean(&data);
  return 0;
}