static char *uuid_get_local(void) {
  char *uuid;

  /* Check /etc/uuid / UUIDFile before any other method. */
  if ((uuid = uuid_get_from_file(uuidfile ? uuidfile : "/etc/uuid")) != NULL)
    return (uuid);

#if defined(__APPLE__)
  if ((uuid = uuid_get_from_sysctlbyname("kern.uuid")) != NULL)
    return (uuid);
#elif defined(__FreeBSD__)
  if ((uuid = uuid_get_from_sysctlbyname("kern.hostuuid")) != NULL)
    return (uuid);
#elif defined(__NetBSD__)
  if ((uuid = uuid_get_from_sysctlbyname("machdep.dmi.system-uuid")) != NULL)
    return (uuid);
#elif defined(__OpenBSD__)
  if ((uuid = uuid_get_from_sysctl()) != NULL)
    return (uuid);
#elif defined(__linux__)
  if ((uuid = uuid_get_from_file("/sys/class/dmi/id/product_uuid")) != NULL)
    return (uuid);
#endif

#if HAVE_LIBHAL_H
  if ((uuid = uuid_get_from_hal()) != NULL)
    return (uuid);
#endif

  if ((uuid = uuid_get_from_dmidecode()) != NULL)
    return (uuid);

#if defined(__linux__)
  if ((uuid = uuid_get_from_file("/sys/hypervisor/uuid")) != NULL)
    return (uuid);
#endif

  return (NULL);
}