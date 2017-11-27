static int cgroups_init(void) {
  if (il_cgroup == NULL)
    il_cgroup = ignorelist_create(1);

  return 0;
}