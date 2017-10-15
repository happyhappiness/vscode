      fprintf (f, "?");
    }
  }
  return (maxwidth - n);
}

static int pad (FILE *f, int col, int i)
{
  char fmt[8];

  if (col < i)
  {
