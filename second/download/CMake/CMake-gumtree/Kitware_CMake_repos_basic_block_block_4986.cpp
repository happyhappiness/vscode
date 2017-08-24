{
  CURLcode result;

  if(!data)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  while(form) {
    if(form->type == FORM_DATA) {
      result = Curl_convert_to_network(data, form->line, form->length);
      /* Curl_convert_to_network calls failf if unsuccessful */
      if(result)
        return result;
    }

    form = form->next;
  }

  return CURLE_OK;
}