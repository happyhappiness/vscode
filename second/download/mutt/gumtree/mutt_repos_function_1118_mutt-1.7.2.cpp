int
#ifdef _LIBC
weak_function
#endif
re_exec (s)
    const char *s;
{
  const int len = strlen (s);
  return
    0 <= re_search (&re_comp_buf, s, len, 0, len, (struct re_registers *) 0);
}