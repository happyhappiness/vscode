void
print_double_string (where, string1, size1, string2, size2)
    const char *where;
    const char *string1;
    const char *string2;
    int size1;
    int size2;
{
  int this_char;

  if (where == NULL)
    printf ("(null)");
  else
    {
      if (FIRST_STRING_P (where))
        {
          for (this_char = where - string1; this_char < size1; this_char++)
            putchar (string1[this_char]);

          where = string2;
        }

      for (this_char = where - string2; this_char < size2; this_char++)
        putchar (string2[this_char]);
    }
}