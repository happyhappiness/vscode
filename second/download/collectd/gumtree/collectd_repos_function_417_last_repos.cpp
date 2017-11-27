static int nut_set_connect_timeout(const char *value) {
#if HAVE_UPSCLI_TRYCONNECT
  long ret;

  errno = 0;
  ret = strtol(value, /* endptr = */ NULL, /* base = */ 10);
  if (errno == 0)
    connect_timeout = ret;
  else
    WARNING("nut plugin: The ConnectTimeout option requires numeric argument. "
            "Setting ignored.");
#else /* #if HAVE_UPSCLI_TRYCONNECT */
  WARNING("nut plugin: Dependency libupsclient version insufficient (<2.6.2) "
          "for ConnectTimeout option support. Setting ignored.");
#endif
  return 0;
}