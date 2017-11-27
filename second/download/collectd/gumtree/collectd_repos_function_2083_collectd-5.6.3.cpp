static char *uuid_get_from_sysctlbyname(const char *name) {
  char uuid[UUID_PRINTABLE_NORMAL_LENGTH + 1];
  size_t len = sizeof(uuid);
  if (sysctlbyname(name, &uuid, &len, NULL, 0) == -1)
    return NULL;
  return (strdup(uuid));
}