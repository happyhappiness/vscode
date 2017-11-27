static int add_domain(struct lv_read_state *state, virDomainPtr dom) {
  domain_t *new_ptr;
  int new_size = sizeof(state->domains[0]) * (state->nr_domains + 1);

  if (state->domains)
    new_ptr = realloc(state->domains, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL)
    return -1;

  state->domains = new_ptr;
  state->domains[state->nr_domains].ptr = dom;
  memset(&state->domains[state->nr_domains].info, 0,
         sizeof(state->domains[state->nr_domains].info));

  return state->nr_domains++;
}