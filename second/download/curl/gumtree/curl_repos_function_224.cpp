static void trace_it (const char *fmt, ...)
{
  static int do_trace = -1;
  va_list args;

  if (do_trace == -1) {
    const char *env = getenv("CURL_TRACE");
    do_trace = (env && atoi(env) > 0);
  }
  if (!do_trace)
    return;
  va_start (args, fmt);
  vfprintf (stderr, fmt, args);
  fflush (stderr);
  va_end (args);
}