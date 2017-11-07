static int buff2type (const char *s)
{
  int type;
  
  for (type = DT_NONE; types[type].machine; type++)
    if (!strcmp (types[type].machine, s))
	return type;
  
  return DT_NONE;
}