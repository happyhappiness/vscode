static void free_domains(struct lv_read_state *state) {
  if (state->domains) {
    for (int i = 0; i < state->nr_domains; ++i)
      virDomainFree(state->domains[i].ptr);
    sfree(state->domains);
  }
  state->domains = NULL;
  state->nr_domains = 0;
}