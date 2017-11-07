char *
_nl_find_language (name)
     const char *name;
{
  while (name[0] != '\0' && name[0] != '_' && name[0] != '@'
	 && name[0] != '+' && name[0] != ',')
    ++name;

  return (char *) name;
}