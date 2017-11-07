static int flowed_visual_strlen (char *l, int i)
{
  int j;
  for (j = 0; *l; l++)
  {
    if (*l == '\t')
      j += 8 - ((i + j) % 8);
    else
      j++;
  }
  
  return j;
}