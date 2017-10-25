static void GetStr(char **string,
		   char *value)
{
  if(*string)
    free(*string);
  *string = strdup(value);
}