static int storebuffer(int output, FILE *data)
{
  char **buffer = (char **)data;
  **buffer = (char)output;
  (*buffer)++;
  return output; /* act like fputc() ! */
}