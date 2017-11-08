static enum protection_level
name_to_level(const char *name)
{
  int i;
  for(i = 0; i < (int)sizeof(level_names)/(int)sizeof(level_names[0]); i++)
    if(curl_strnequal(level_names[i].name, name, strlen(name)))
      return level_names[i].level;
  return (enum protection_level)-1;
}