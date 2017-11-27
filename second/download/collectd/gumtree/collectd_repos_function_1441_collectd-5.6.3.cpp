cu_mount_t *cu_mount_getlist(cu_mount_t **list) {
  cu_mount_t *new;
  cu_mount_t *first = NULL;
  cu_mount_t *last = NULL;

  if (list == NULL)
    return (NULL);

  if (*list != NULL) {
    first = *list;
    last = first;
    while (last->next != NULL)
      last = last->next;
  }

#if HAVE_LISTMNTENT && 0
  new = cu_mount_listmntent();
#elif HAVE_GETVFSSTAT || HAVE_GETFSSTAT
  new = cu_mount_getfsstat();
#elif HAVE_TWO_GETMNTENT || HAVE_GEN_GETMNTENT || HAVE_SUN_GETMNTENT
  new = cu_mount_gen_getmntent();
#elif HAVE_SEQ_GETMNTENT
#error "This version of `getmntent' hat not yet been implemented!"
#elif HAVE_ONE_GETMNTENT
  new = cu_mount_getmntent();
#else
#error "Could not determine how to find mountpoints."
#endif

  if (first != NULL) {
    last->next = new;
  } else {
    first = new;
    last = new;
    *list = first;
  }

  while ((last != NULL) && (last->next != NULL))
    last = last->next;

  return (last);
}