static int pmu_add_events(struct eventlist *el, uint32_t type,
                          event_info_t *events, size_t count) {

  for (size_t i = 0; i < count; i++) {
    /* Allocate memory for event struct that contains array of efd structs
       for all cores */
    struct event *e =
        calloc(sizeof(struct event) + sizeof(struct efd) * el->num_cpus, 1);
    if (e == NULL) {
      ERROR(PMU_PLUGIN ": Failed to allocate event structure");
      return -ENOMEM;
    }

    e->attr.type = type;
    e->attr.config = events[i].config;
    e->attr.size = PERF_ATTR_SIZE_VER0;
    if (!el->eventlist)
      el->eventlist = e;
    if (el->eventlist_last)
      el->eventlist_last->next = e;
    el->eventlist_last = e;
    e->event = strdup(events[i].name);
  }

  return 0;
}