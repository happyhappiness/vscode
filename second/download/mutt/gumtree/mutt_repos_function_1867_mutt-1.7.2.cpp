static void char_to_escape (char *dest, unsigned int c)
{
  switch (c)
  {
    case '\r': strcpy (dest, "\\r"); break;	/* __STRCPY_CHECKED__ */
    case '\n': strcpy (dest, "\\n"); break;	/* __STRCPY_CHECKED__ */
    case '\t': strcpy (dest, "\\t"); break;	/* __STRCPY_CHECKED__ */
    case '\f': strcpy (dest, "\\f"); break;	/* __STRCPY_CHECKED__ */
    default: sprintf (dest, "\\%03o", c); break;
  }
}