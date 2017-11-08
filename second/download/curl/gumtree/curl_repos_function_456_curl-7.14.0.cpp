CURLMcode curl_multi_cleanup(CURLM *multi_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  struct Curl_one_easy *nexteasy;

  if(GOOD_MULTI_HANDLE(multi)) {
    multi->type = 0; /* not good anymore */
    Curl_hash_destroy(multi->hostcache);

    /* remove all easy handles */
    easy = multi->easy.next;
    while(easy) {
      nexteasy=easy->next;
      /* clear out the usage of the shared DNS cache */
      easy->easy_handle->hostcache = NULL;
      Curl_easy_addmulti(easy->easy_handle, NULL); /* clear the association */

      if (easy->msg)
        free(easy->msg);
      free(easy);
      easy = nexteasy;
    }

    free(multi);

    return CURLM_OK;
  }
  else
    return CURLM_BAD_HANDLE;
}