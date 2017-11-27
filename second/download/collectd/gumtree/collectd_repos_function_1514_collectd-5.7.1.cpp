int cu_mount_type(const char *type) {
  if (strcmp(type, "ext3") == 0)
    return CUMT_EXT3;
  if (strcmp(type, "ext2") == 0)
    return CUMT_EXT2;
  if (strcmp(type, "ufs") == 0)
    return CUMT_UFS;
  if (strcmp(type, "vxfs") == 0)
    return CUMT_VXFS;
  if (strcmp(type, "zfs") == 0)
    return CUMT_ZFS;
  return CUMT_UNKNOWN;
}