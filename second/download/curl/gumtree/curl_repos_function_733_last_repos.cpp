void win32_perror(const char *msg)
{
  char buf[512];
  DWORD err = SOCKERRNO;

  if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                    LANG_NEUTRAL, buf, sizeof(buf), NULL))
     snprintf(buf, sizeof(buf), "Unknown error %lu (%#lx)", err, err);
  if(msg)
    fprintf(stderr, "%s: ", msg);
  fprintf(stderr, "%s\n", buf);
}