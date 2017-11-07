int mutt_getvaluebychar (char ch, struct mapping_t *table)
{
  int i;

  for (i = 0; table[i].name; i++)
  {
    if (ch == table[i].name[0])
      return table[i].value;
  }

  return (-1);
}