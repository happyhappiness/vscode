static void fix_end_of_file (const char *data)
{
  FILE *fp;
  int c;
  
  if ((fp = safe_fopen (data, "a+")) == NULL)
    return;
  fseek (fp,-1,SEEK_END);
  if ((c = fgetc(fp)) != '\n')
    fputc ('\n', fp);
  safe_fclose (&fp);
}