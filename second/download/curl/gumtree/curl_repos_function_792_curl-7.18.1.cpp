static void add_closure(struct Curl_multi *multi,
                        struct SessionHandle *data)
{
  int i;
  struct closure *cl = (struct closure *)calloc(sizeof(struct closure), 1);
  struct closure *p=NULL;
  struct closure *n;
  if(cl) {
    cl->easy_handle = data;
    cl->next = multi->closure;
    multi->closure = cl;
  }

  p = multi->closure;
  cl = p->next; /* start immediately on the second since the first is the one
                   we just added and it is _very_ likely to actually exist
                   used in the cache since that's the whole purpose of adding
                   it to this list! */

  /* When adding, scan through all the other currently kept handles and see if
     there are any connections still referring to them and kill them if not. */
  while(cl) {
    bool inuse = FALSE;
    for(i=0; i< multi->connc->num; i++) {
      if(multi->connc->connects[i] &&
         (multi->connc->connects[i]->data == cl->easy_handle)) {
        inuse = TRUE;
        break;
      }
    }

    n = cl->next;

    if(!inuse) {
      /* cl->easy_handle is now killable */
      infof(data, "Delayed kill of easy handle %p\n", cl->easy_handle);
      /* unmark it as not having a connection around that uses it anymore */
      cl->easy_handle->state.shared_conn= NULL;
      Curl_close(cl->easy_handle);
      if(p)
        p->next = n;
      else
        multi->closure = n;
      free(cl);
    }
    else
      p = cl;

    cl = n;
  }

}