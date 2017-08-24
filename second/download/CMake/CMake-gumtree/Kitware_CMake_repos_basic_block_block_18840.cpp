{
  int (*dynamic_pthread_setname_np)(const char* name);
  char namebuf[64];  /* MAXTHREADNAMESIZE */
  int err;

  /* pthread_setname_np() first appeared in OS X 10.6 and iOS 3.2. */
  *(void **)(&dynamic_pthread_setname_np) =
      dlsym(RTLD_DEFAULT, "pthread_setname_np");

  if (dynamic_pthread_setname_np == NULL)
    return -ENOSYS;

  strncpy(namebuf, name, sizeof(namebuf) - 1);
  namebuf[sizeof(namebuf) - 1] = '\0';

  err = dynamic_pthread_setname_np(namebuf);
  if (err)
    return -err;

  return 0;
}