static void
print_and_abort (void)
{
  /* Don't change any of these strings.  Yes, it would be possible to add
     the newline to the string and use fputs or so.  But this must not
     happen because the "memory exhausted" message appears in other places
     like this and the translation should be reused instead of creating
     a very similar string which requires a separate translation.  */
# ifdef _LIBC
  (void) __fxprintf (NULL, "%s\n", _("memory exhausted"));
# else
  fprintf (stderr, "%s\n", _("memory exhausted"));
# endif
  exit (1);
}