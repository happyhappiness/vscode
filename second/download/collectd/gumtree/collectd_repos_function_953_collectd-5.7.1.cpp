static int check_permissions(void) {

  if (getuid() == 0) {
    /* We have everything we need */
    return 0;
#if !defined(HAVE_SYS_CAPABILITY_H) && !defined(CAP_SYS_RAWIO)
  } else {
    ERROR("turbostat plugin: Initialization failed: this plugin "
          "requires collectd to run as root");
    return -1;
  }
#else  /* HAVE_SYS_CAPABILITY_H && CAP_SYS_RAWIO */
  }