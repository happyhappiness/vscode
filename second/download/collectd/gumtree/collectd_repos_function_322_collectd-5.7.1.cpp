static int cgroup_set(rdt_core_group_t *cg, char *desc, uint64_t *cores,
                      size_t num_cores) {
  assert(cg != NULL);
  assert(desc != NULL);
  assert(cores != NULL);
  assert(num_cores > 0);

  cg->cores = calloc(num_cores, sizeof(unsigned));
  if (cg->cores == NULL) {
    ERROR(RDT_PLUGIN ": Error allocating core group table");
    return (-ENOMEM);
  }
  cg->num_cores = num_cores;
  cg->desc = strdup(desc);
  if (cg->desc == NULL) {
    ERROR(RDT_PLUGIN ": Error allocating core group description");
    sfree(cg->cores);
    return (-ENOMEM);
  }

  for (size_t i = 0; i < num_cores; i++)
    cg->cores[i] = (unsigned)cores[i];

  return 0;
}