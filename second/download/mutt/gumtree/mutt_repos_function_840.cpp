static int count_delete_lines (FILE *fp, BODY *b, LOFF_T *length, size_t datelen)
{
  int dellines = 0;
  long l;
  int ch;

  if (b->deleted)
  {
    fseeko (fp, b->offset, SEEK_SET);
    for (l = b->length ; l ; l --)
    {
      ch = getc (fp);
      if (ch == EOF)
	break;
      if (ch == '\n')
	dellines ++;
    }
    dellines -= 3;
    *length -= b->length - (84 + datelen);
    /* Count the number of digits exceeding the first one to write the size */
    for (l = 10 ; b->length >= l ; l *= 10)
      (*length) ++;
  }
  else
  {
    for (b = b->parts ; b ; b = b->next)
      dellines += count_delete_lines (fp, b, length, datelen);
  }
  return dellines;
}