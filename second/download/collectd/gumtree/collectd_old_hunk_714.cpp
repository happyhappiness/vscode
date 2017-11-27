  vsnprintf(message, sizeof(message), format, ap);
  message[sizeof(message) - 1] = '\0';
  va_end(ap);

  plugin_log(level, "%s", message);
} /* c_release */

/* vim: set sw=4 ts=4 tw=78 noexpandtab : */
