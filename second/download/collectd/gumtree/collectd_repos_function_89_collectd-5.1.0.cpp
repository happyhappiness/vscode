char *
lt__strdup (const char *string)
{
  return (char *) lt__memdup (string, strlen (string) +1);
}