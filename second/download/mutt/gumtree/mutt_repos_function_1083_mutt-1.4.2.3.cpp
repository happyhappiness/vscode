static void print_userid (const char *id)
{
  for (; id && *id; id++)
  {
    if (*id >= ' ' && *id <= 'z' && *id != ':')
      putchar (*id);
    else
      printf ("\\x%02x", (*id) & 0xff);
  }
}