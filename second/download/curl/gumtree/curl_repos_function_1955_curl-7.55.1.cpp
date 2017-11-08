static struct passwd * vms_getpwuid(uid_t uid)
{
  struct passwd * my_passwd;

/* Hack needed to support 64 bit builds, decc_getpwnam is 32 bit only */
#ifdef __DECC
#   if __INITIAL_POINTER_SIZE
  __char_ptr32 unix_path;
#   else
  char *unix_path;
#   endif
#else
  char *unix_path;
#endif

  my_passwd = decc_getpwuid(uid);
  if(my_passwd == NULL) {
    return my_passwd;
  }

  unix_path = vms_translate_path(my_passwd->pw_dir);

  if((long)unix_path <= 0) {
    /* We can not translate it, so return the original string */
    return my_passwd;
  }

  /* If no changes needed just return it */
  if(unix_path == my_passwd->pw_dir) {
    return my_passwd;
  }

  /* Need to copy the structure returned */
  /* Since curl is only using pw_dir, no need to fix up */
  /* the pw_shell when running under Bash */
  vms_passwd_cache.pw_name = my_passwd->pw_name;
  vms_passwd_cache.pw_uid = my_passwd->pw_uid;
  vms_passwd_cache.pw_gid = my_passwd->pw_uid;
  vms_passwd_cache.pw_dir = unix_path;
  vms_passwd_cache.pw_shell = my_passwd->pw_shell;

  return &vms_passwd_cache;
}