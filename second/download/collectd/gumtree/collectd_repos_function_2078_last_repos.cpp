static int madwifi_read(void) {
  int rv;
  int sk;

  if (init_state == 0)
    madwifi_real_init();
  init_state = 2;

  sk = socket(AF_INET, SOCK_DGRAM, 0);
  if (sk < 0)
    return -1;

  /* procfs iteration is not safe because it does not check whether given
     interface is madwifi interface and there are private ioctls used, which
     may do something completely different on non-madwifi devices.
     Therefore, it is not used unless explicitly enabled (and should be used
     together with ignorelist). */

  if (use_sysfs)
    rv = sysfs_iterate(sk);
  else
    rv = procfs_iterate(sk);

  close(sk);

  return rv;
}