int DumpFile(char* filename, char* comment)
{
  FILE* file = fopen(filename, "r");
  if(!file)
    {
    printf("Error, could not open file %s\n", filename);
    return 1;
    }
  printf("%s", comment);
  while(!feof(file))
    {
    int ch = fgetc(file);
    if(ch != EOF)
      {
      if(ch == '<')
        {
        printf("&lt;");
        }
      else if(ch == '>')
        {
        printf("&gt;");
        }
      else if(ch == '&')
        {
        printf("&amp;");
        }
      else 
        {
        putc(ch, stdout);
        }
      }
    }
  printf("\n");
  fclose(file);
  return 0;
}