void init_extended_keys(void)
{
#ifdef NCURSES_VERSION
  int j;

  use_extended_names(TRUE);

  for (j = 0; KeyNames[j].name; ++j)
  {
    if (KeyNames[j].value == -1)
    {
      const char *keyname = find_ext_name(KeyNames[j].name);

      if (keyname)
      {
        char *s = tigetstr((char *)keyname);
	if (s && (long)(s) != -1)
	{
	  int code = key_defined(s);
	  if (code > 0)
	    KeyNames[j].value = code;
	}
      }
    }
  }
#endif
}