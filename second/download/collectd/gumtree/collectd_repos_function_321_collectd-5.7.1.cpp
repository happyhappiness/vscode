static int cgroup_cmp(const rdt_core_group_t *cg_a,
                      const rdt_core_group_t *cg_b) {
  int found = 0;

  assert(cg_a != NULL);
  assert(cg_b != NULL);

  const int sz_a = cg_a->num_cores;
  const int sz_b = cg_b->num_cores;
  const unsigned *tab_a = cg_a->cores;
  const unsigned *tab_b = cg_b->cores;

  for (int i = 0; i < sz_a; i++) {
    for (int j = 0; j < sz_b; j++)
      if (tab_a[i] == tab_b[j])
        found++;
  }
  /* if no cores are the same */
  if (!found)
    return 0;
  /* if group contains same cores */
  if (sz_a == sz_b && sz_b == found)
    return 1;
  /* if not all cores are the same */
  return -1;
}