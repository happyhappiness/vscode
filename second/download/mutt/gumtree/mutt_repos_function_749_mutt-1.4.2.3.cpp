static int flush_doc (int docstat, FILE *out)
{
  if (docstat & D_INIT)
    return D_INIT;

  if (fd_recurse++)
  {
    fprintf (stderr, "%s: Internal error, recursion in flush_doc()!\n", Progname);
    exit (1);
  }

  if (docstat & (D_TAB))
    docstat = print_it (SP_END_TAB, NULL, out, docstat);

  if (docstat & (D_DL))
    docstat = print_it (SP_END_DL, NULL, out, docstat);

  if (docstat & (D_EM | D_BF))
    docstat = print_it (SP_END_FT, NULL, out, docstat);

  docstat = print_it (SP_NEWLINE, NULL, out, 0);

  fd_recurse--;
  return D_INIT;
}