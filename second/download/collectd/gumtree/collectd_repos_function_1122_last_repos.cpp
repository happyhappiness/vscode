static disk_t *get_disk(cfg_disk_t *cd, const char *name) /* {{{ */
{
  disk_t *d;

  if ((cd == NULL) || (name == NULL))
    return NULL;

  for (d = cd->disks; d != NULL; d = d->next) {
    if (strcmp(d->name, name) == 0)
      return d;
  }

  d = calloc(1, sizeof(*d));
  if (d == NULL)
    return NULL;
  d->next = NULL;

  d->name = strdup(name);
  if (d->name == NULL) {
    sfree(d);
    return NULL;
  }

  d->next = cd->disks;
  cd->disks = d;

  return d;
}