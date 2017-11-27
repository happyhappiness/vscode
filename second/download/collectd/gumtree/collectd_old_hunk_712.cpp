  vsnprintf(buffer, sizeof(buffer), format, ap);
  va_end(ap);

  printf("plugin_log (%i, \"%s\");\n", level, buffer);
}

cdtime_t plugin_get_interval(void) { return TIME_T_TO_CDTIME_T(10); }

/* vim: set sw=2 sts=2 et : */
