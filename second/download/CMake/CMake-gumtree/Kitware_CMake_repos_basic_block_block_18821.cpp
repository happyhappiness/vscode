{
  struct passwd pw;
  struct passwd* result;
  char* buf;
  uid_t uid;
  size_t bufsize;
  size_t name_size;
  size_t homedir_size;
  size_t shell_size;
  long initsize;
  int r;
#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
  int (*getpwuid_r)(uid_t, struct passwd*, char*, size_t, struct passwd**);

  getpwuid_r = dlsym(RTLD_DEFAULT, "getpwuid_r");
  if (getpwuid_r == NULL)
    return -ENOSYS;
#endif

  if (pwd == NULL)
    return -EINVAL;

  initsize = sysconf(_SC_GETPW_R_SIZE_MAX);

  if (initsize <= 0)
    bufsize = 4096;
  else
    bufsize = (size_t) initsize;

  uid = geteuid();
  buf = NULL;

  for (;;) {
    uv__free(buf);
    buf = uv__malloc(bufsize);

    if (buf == NULL)
      return -ENOMEM;

    r = getpwuid_r(uid, &pw, buf, bufsize, &result);

    if (r != ERANGE)
      break;

    bufsize *= 2;
  }

  if (r != 0) {
    uv__free(buf);
    return -r;
  }

  if (result == NULL) {
    uv__free(buf);
    return -ENOENT;
  }

  /* Allocate memory for the username, shell, and home directory */
  name_size = strlen(pw.pw_name) + 1;
  homedir_size = strlen(pw.pw_dir) + 1;
  shell_size = strlen(pw.pw_shell) + 1;
  pwd->username = uv__malloc(name_size + homedir_size + shell_size);

  if (pwd->username == NULL) {
    uv__free(buf);
    return -ENOMEM;
  }

  /* Copy the username */
  memcpy(pwd->username, pw.pw_name, name_size);

  /* Copy the home directory */
  pwd->homedir = pwd->username + name_size;
  memcpy(pwd->homedir, pw.pw_dir, homedir_size);

  /* Copy the shell */
  pwd->shell = pwd->homedir + homedir_size;
  memcpy(pwd->shell, pw.pw_shell, shell_size);

  /* Copy the uid and gid */
  pwd->uid = pw.pw_uid;
  pwd->gid = pw.pw_gid;

  uv__free(buf);

  return 0;
}