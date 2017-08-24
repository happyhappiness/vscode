{
    /* copy the first entry to 'tv' */
    memcpy(tv, &node->time, sizeof(*tv));

    /* remove first entry from list */
    Curl_llist_remove(list, e, NULL);

    /* insert this node again into the splay */
    multi->timetree = Curl_splayinsert(*tv, multi->timetree,
                                       &d->state.timenode);
  }