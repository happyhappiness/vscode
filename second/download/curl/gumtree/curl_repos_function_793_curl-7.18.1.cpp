void curl_multi_dump(CURLM *multi_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  int i;
  fprintf(stderr, "* Multi status: %d handles, %d alive\n",
          multi->num_easy, multi->num_alive);
  for(easy=multi->easy.next; easy != &multi->easy; easy = easy->next) {
    if(easy->state != CURLM_STATE_COMPLETED) {
      /* only display handles that are not completed */
      fprintf(stderr, "handle %p, state %s, %d sockets\n",
              (void *)easy->easy_handle,
              statename[easy->state], easy->numsocks);
      for(i=0; i < easy->numsocks; i++) {
        curl_socket_t s = easy->sockets[i];
        struct Curl_sh_entry *entry =
          Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(s));

        fprintf(stderr, "%d ", (int)s);
        if(!entry) {
          fprintf(stderr, "INTERNAL CONFUSION\n");
          continue;
        }
        fprintf(stderr, "[%s %s] ",
                entry->action&CURL_POLL_IN?"RECVING":"",
                entry->action&CURL_POLL_OUT?"SENDING":"");
      }
      if(easy->numsocks)
        fprintf(stderr, "\n");
    }
  }
}