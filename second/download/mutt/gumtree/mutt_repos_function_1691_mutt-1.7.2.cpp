static void matches_ensure_morespace(int current)
{
  int base_space, extra_space, space;

  if (current > Matches_listsize - 2)
  {
    base_space = MAX(NUMVARS,NUMCOMMANDS) + 1; 
    extra_space = Matches_listsize - base_space;
    extra_space *= 2;
    space = base_space + extra_space;
    safe_realloc (&Matches, space * sizeof (char *));
    memset (&Matches[current + 1], 0, space - current);
    Matches_listsize = space;
  }
}