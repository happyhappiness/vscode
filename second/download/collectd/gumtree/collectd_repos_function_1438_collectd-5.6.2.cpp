static cu_mount_t *cu_mount_gen_getmntent(void) {
  struct mnttab mt;
  FILE *fp;

  cu_mount_t *first = NULL;
  cu_mount_t *last = NULL;
  cu_mount_t *new = NULL;

  DEBUG("utils_mount: (void); COLLECTD_MNTTAB = %s", COLLECTD_MNTTAB);

  if ((fp = fopen(COLLECTD_MNTTAB, "r")) == NULL) {
    char errbuf[1024];
    ERROR("fopen (%s): %s", COLLECTD_MNTTAB,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (NULL);
  }

  while (getmntent(fp, &mt) == 0) {
    if ((new = calloc(1, sizeof(*new))) == NULL)
      break;

    /* Copy values from `struct mnttab' */
    new->dir = sstrdup(mt.mnt_mountp);
    new->spec_device = sstrdup(mt.mnt_special);
    new->type = sstrdup(mt.mnt_fstype);
    new->options = sstrdup(mt.mnt_mntopts);
    new->device = get_device_name(new->options);
    new->next = NULL;

    /* Append to list */
    if (first == NULL) {
      first = new;
      last = new;
    } else {
      last->next = new;
      last = new;
    }
  }

  fclose(fp);

  return (first);
}