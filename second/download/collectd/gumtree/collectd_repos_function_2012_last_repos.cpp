static int pmu_setup_events(struct eventlist *el, bool measure_all,
                            int measure_pid) {
  struct event *e, *leader = NULL;
  int ret = -1;

  for (e = el->eventlist; e; e = e->next) {

    for (int i = 0; i < el->num_cpus; i++) {
      if (setup_event(e, i, leader, measure_all, measure_pid) < 0) {
        WARNING(PMU_PLUGIN ": perf event '%s' is not available (cpu=%d).",
                e->event, i);
      } else {
        /* success if at least one event was set */
        ret = 0;
      }
    }

    if (e->group_leader)
      leader = e;
    if (e->end_group)
      leader = NULL;
  }

  return ret;
}