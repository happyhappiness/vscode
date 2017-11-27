static int df_init(void) {
  if (il_device == NULL)
    il_device = ignorelist_create(1);
  if (il_mountpoint == NULL)
    il_mountpoint = ignorelist_create(1);
  if (il_fstype == NULL)
    il_fstype = ignorelist_create(1);

  return (0);
}