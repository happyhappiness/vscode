static char *getflagstr(int flags)
{
  char *buf = malloc(256);
  if(buf) {
    snprintf(buf, 256, "%s,%s,%s,%s",
      ((flags & SANITIZE_ALLOW_COLONS) ? "SANITIZE_ALLOW_COLONS" : ""),
      ((flags & SANITIZE_ALLOW_PATH) ? "SANITIZE_ALLOW_PATH" : ""),
      ((flags & SANITIZE_ALLOW_RESERVED) ? "SANITIZE_ALLOW_RESERVED" : ""),
      ((flags & SANITIZE_ALLOW_TRUNCATE) ? "SANITIZE_ALLOW_TRUNCATE" : ""));
  }
  return buf;
}