static void pmu_dump_events() {

  DEBUG(PMU_PLUGIN ": Events:");

  struct event *e;

  for (e = g_ctx.event_list->eventlist; e; e = e->next) {
    DEBUG(PMU_PLUGIN ":   event       : %s", e->event);
    DEBUG(PMU_PLUGIN ":     group_lead: %d", e->group_leader);
    DEBUG(PMU_PLUGIN ":     end_group : %d", e->end_group);
    DEBUG(PMU_PLUGIN ":     type      : %#x", e->attr.type);
    DEBUG(PMU_PLUGIN ":     config    : %#x", (unsigned)e->attr.config);
    DEBUG(PMU_PLUGIN ":     size      : %d", e->attr.size);
  }
}