static int put_zfs_value(kstat_t *ksp, char const *k, value_t v) {
  llentry_t *e;
  char *k_copy;
  value_t *v_copy;

  k_copy = strdup(k);
  if (k_copy == NULL)
    return ENOMEM;

  v_copy = malloc(sizeof(*v_copy));
  if (v_copy == NULL) {
    sfree(k_copy);
    return ENOMEM;
  }
  *v_copy = v;

  e = llentry_create(k_copy, v_copy);
  if (e == NULL) {
    sfree(v_copy);
    sfree(k_copy);
    return ENOMEM;
  }

  llist_append(ksp, e);
  return 0;
}