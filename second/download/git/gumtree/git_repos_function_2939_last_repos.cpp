static int
do_getc (void)
{
  int c = getc (stdin);

  if (c == EOF)
    {
      if (ferror (stdin))
	error ("error while reading standard input");
    }

  return c;
}