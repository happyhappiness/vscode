static int init(int num, CURLM *cm, const char *url, const char *userpwd,
                struct curl_slist *headers)
{
  int res = 0;

  res_easy_init(eh[num]);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_URL, url);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXY, PROXY);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXYUSERPWD, userpwd);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXYAUTH, (long)CURLAUTH_ANY);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_VERBOSE, 1L);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_HEADER, 1L);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_HTTPHEADER, headers); /* custom Host: */
  if(res)
    goto init_failed;

  res_multi_add_handle(cm, eh[num]);
  if(res)
    goto init_failed;

  return 0; /* success */

init_failed:

  curl_easy_cleanup(eh[num]);
  eh[num] = NULL;

  return res; /* failure */
}