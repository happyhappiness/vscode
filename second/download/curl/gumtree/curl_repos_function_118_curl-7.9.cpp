static void GetStr(char **string,
		   const char *value)
{
  if(*string)
    free(*string);
  *string = strdup(value);
}