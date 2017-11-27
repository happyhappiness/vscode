static cu_mount_t *cu_mount_getmntent(void) {
  FILE *fp;
  struct mntent me;
  char mntbuf[1024];

  cu_mount_t *first = NULL;
  cu_mount_t *last = NULL;
  cu_mount_t *new = NULL;

  DEBUG("utils_mount: (void); COLLECTD_MNTTAB = %s", COLLECTD_MNTTAB);

  if ((fp = setmntent(COLLECTD_MNTTAB, "r")) == NULL) {
    char errbuf[1024];
    ERROR("setmntent (%s): %s", COLLECTD_MNTTAB,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (NULL);
  }

  while (getmntent_r(fp, &me, mntbuf, sizeof(mntbuf))) {
    if ((new = calloc(1, sizeof(*new))) == NULL)
      break;

    /* Copy values from `struct mntent *' */
    new->dir = sstrdup(me.mnt_dir);
    new->spec_device = sstrdup(me.mnt_fsname);
    new->type = sstrdup(me.mnt_type);
    new->options = sstrdup(me.mnt_opts);
    new->device = get_device_name(new->options);
    new->next = NULL;

    DEBUG("utils_mount: new = {dir = %s, spec_device = %s, type = %s, options "
          "= %s, device = %s}",
          new->dir, new->spec_device, new->type, new->options, new->device);

    /* Append to list */
    if (first == NULL) {
      first = new;
      last = new;
    } else {
      last->next = new;
      last = new;
    }
  }

  endmntent(fp);

  DEBUG("utils_mount: return (0x%p)", (void *)first);

  return (first);
}