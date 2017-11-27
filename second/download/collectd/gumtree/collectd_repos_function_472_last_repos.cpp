static void ovs_stats_free_bridge_list(bridge_list_t *head) {
  for (bridge_list_t *i = head; i != NULL;) {
    bridge_list_t *del = i;
    i = i->next;
    sfree(del->name);
    sfree(del);
  }
}