    return 0;
  }
  fprintf(stderr, "You can only select one HTTP request!\n");
  return 1;
}

static void helpf(const char *fmt, ...)
{
  va_list ap;
  if(fmt) {
    va_start(ap, fmt);
    fputs("curl: ", stderr); /* prefix it */
    vfprintf(stderr, fmt, ap);
