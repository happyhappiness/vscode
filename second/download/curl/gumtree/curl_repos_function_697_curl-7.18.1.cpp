static void signalPipeClose(struct curl_llist *pipeline)
{
  struct curl_llist_element *curr;

  if(!pipeline)
    return;

  curr = pipeline->head;
  while(curr) {
    struct curl_llist_element *next = curr->next;
    struct SessionHandle *data = (struct SessionHandle *) curr->ptr;

#ifdef CURLDEBUG /* debug-only code */
    if(data->magic != CURLEASY_MAGIC_NUMBER) {
      /* MAJOR BADNESS */
      infof(data, "signalPipeClose() found BAAD easy handle\n");
    }
#endif

    data->state.pipe_broke = TRUE;
    Curl_multi_handlePipeBreak(data);
    Curl_llist_remove(pipeline, curr, NULL);
    curr = next;
  }
}