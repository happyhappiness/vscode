struct curl_slist *curl_slist_append(struct curl_slist *list,

                                     const char *data)

{

  struct curl_slist     *last;

  struct curl_slist     *new_item;



  new_item = (struct curl_slist *) malloc(sizeof(struct curl_slist));

  if (new_item) {

    new_item->next = NULL;

    new_item->data = strdup(data);

  }

  if (new_item == NULL || new_item->data == NULL) {

    fprintf(stderr, "Cannot allocate memory for QUOTE list.\n");

    return NULL;

  }



  if (list) {

    last = slist_get_last(list);

    last->next = new_item;

    return list;

  }



  /* if this is the first item, then new_item *is* the list */

  return new_item;

}



/* be nice and clean up resources */

void curl_slist_free_all(struct curl_slist *list)

{

  struct curl_slist     *next;

  struct curl_slist     *item;



  if (!list)

    return;



  item = list;

  do {

    next = item->next;

                

    if (item->data) {

      free(item->data);

    }

    free(item);

    item = next;

  } while (next);

}



/* Curl_infof() is for info message along the way */



void Curl_infof(struct SessionHandle *data, const char *fmt, ...)

{

  va_list ap;

  if(data->set.verbose) {

    char print_buffer[1024 + 1];

    va_start(ap, fmt);

    vsnprintf(print_buffer, 1024, fmt, ap);

    va_end(ap);

    Curl_debug(data, CURLINFO_TEXT, print_buffer, strlen(print_buffer));

  }

}



