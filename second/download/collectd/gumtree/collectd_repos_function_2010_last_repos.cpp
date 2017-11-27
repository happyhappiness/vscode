static int pmu_add_hw_events(struct eventlist *el, char **e, size_t count) {

  for (size_t i = 0; i < count; i++) {

    size_t group_events_count = 0;

    char *events = strdup(e[i]);
    if (!events)
      return -1;

    char *s, *tmp;
    for (s = strtok_r(events, ",", &tmp); s; s = strtok_r(NULL, ",", &tmp)) {

      /* Multiple events parsed in one entry */
      if (group_events_count == 1) {
        /* Mark previously added event as group leader */
        el->eventlist_last->group_leader = 1;
      }

      /* Allocate memory for event struct that contains array of efd structs
         for all cores */
      struct event *e =
          calloc(sizeof(struct event) + sizeof(struct efd) * el->num_cpus, 1);
      if (e == NULL) {
        free(events);
        return -ENOMEM;
      }

      if (resolve_event(s, &e->attr) == 0) {
        e->next = NULL;
        if (!el->eventlist)
          el->eventlist = e;
        if (el->eventlist_last)
          el->eventlist_last->next = e;
        el->eventlist_last = e;
        e->event = strdup(s);
      } else {
        DEBUG(PMU_PLUGIN ": Cannot resolve %s", s);
        sfree(e);
      }

      group_events_count++;
    }

    /* Multiple events parsed in one entry */
    if (group_events_count > 1) {
      /* Mark last added event as group end */
      el->eventlist_last->end_group = 1;
    }

    free(events);
  }

  return 0;
}