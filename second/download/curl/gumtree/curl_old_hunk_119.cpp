  /* if user didn't hit ENTER, terminate buffer */
  if (i==buflen)
    buffer[buflen-1]=0;

  return buffer; /* we always return success */
}
#endif

#endif /* ifndef HAVE_GETPASS_R */

#if 0
/* for consistensy, here's the old-style function: */
char *getpass(const char *prompt)
{
  static char buf[256];
  return getpass_r(prompt, buf, sizeof(buf));
}
#endif
