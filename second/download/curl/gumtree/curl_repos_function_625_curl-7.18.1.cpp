CURLcode Curl_formconvert(struct SessionHandle *data, struct FormData *form)
{
  struct FormData *next;
  CURLcode rc;

  if(!form)
    return CURLE_OK;

  if(!data)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  do {
    next=form->next;  /* the following form line */
    if(form->type == FORM_DATA) {
      rc = Curl_convert_to_network(data, form->line, form->length);
      /* Curl_convert_to_network calls failf if unsuccessful */
      if(rc != CURLE_OK)
        return rc;
    }
  } while((form = next) != NULL); /* continue */
  return CURLE_OK;
}