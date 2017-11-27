static void ovs_stats_free_port_list(port_list_t *head) {
  for (port_list_t *i = head; i != NULL;) {
    port_list_t *del = i;
    i = i->next;
    sfree(del);
  }
}