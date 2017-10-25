CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
                                   CURL *curl_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;

  /* First, make some basic checks that the CURLM handle is a good handle */
  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  /* Verify that we got a somewhat good easy handle too */
  if(!GOOD_EASY_HANDLE(curl_handle))
    return CURLM_BAD_EASY_HANDLE;

  /* scan through the list and remove the 'curl_handle' */
  easy = multi->easy.next;
  while(easy) {
    if(easy->easy_handle == (struct SessionHandle *)curl_handle)
      break;
    easy=easy->next;
  }
  if(easy) {
    /* If the 'state' is not INIT or COMPLETED, we might need to do something
       nice to put the easy_handle in a good known state when this returns. */

    /* clear out the usage of the shared DNS cache */
    easy->easy_handle->hostcache = NULL;
    Curl_easy_addmulti(easy->easy_handle, NULL); /* clear the association
                                                    to this multi handle */

    /* make the previous node point to our next */
    if(easy->prev)
      easy->prev->next = easy->next;
    /* make our next point to our previous node */
    if(easy->next)
      easy->next->prev = easy->prev;

    /* NOTE NOTE NOTE
       We do not touch the easy handle here! */
    if (easy->msg)
      free(easy->msg);
    free(easy);

    multi->num_easy--; /* one less to care about now */

    return CURLM_OK;
  }
  else
    return CURLM_BAD_EASY_HANDLE; /* twasn't found */
}