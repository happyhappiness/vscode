static void pmu_free_events(struct eventlist *el) {

  if (el == NULL)
    return;

  struct event *e = el->eventlist;

  while (e) {
    struct event *next = e->next;
    sfree(e);
    e = next;
  }

  el->eventlist = NULL;
}