static void skip(const char **date)
{
  /* skip everything that aren't letters or digits */
  while(**date && !isalnum((int)**date))
    (*date)++;
}