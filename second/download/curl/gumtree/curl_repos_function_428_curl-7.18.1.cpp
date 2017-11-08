static bool
checkhttpprefix(struct SessionHandle *data,
                const char *s)
{
  struct curl_slist *head = data->set.http200aliases;
  bool rc = FALSE;
#ifdef CURL_DOES_CONVERSIONS
  /* convert from the network encoding using a scratch area */
  char *scratch = calloc(1, strlen(s)+1);
  if(NULL == scratch) {
     failf (data, "Failed to calloc memory for conversion!");
     return FALSE; /* can't return CURLE_OUT_OF_MEMORY so return FALSE */
  }
  strcpy(scratch, s);
  if(CURLE_OK != Curl_convert_from_network(data, scratch, strlen(s)+1)) {
    /* Curl_convert_from_network calls failf if unsuccessful */
     free(scratch);
     return FALSE; /* can't return CURLE_foobar so return FALSE */
  }
  s = scratch;
#endif /* CURL_DOES_CONVERSIONS */

  while(head) {
    if(checkprefix(head->data, s)) {
      rc = TRUE;
      break;
    }
    head = head->next;
  }

  if((rc != TRUE) && (checkprefix("HTTP/", s))) {
    rc = TRUE;
  }

#ifdef CURL_DOES_CONVERSIONS
  free(scratch);
#endif /* CURL_DOES_CONVERSIONS */
  return rc;
}