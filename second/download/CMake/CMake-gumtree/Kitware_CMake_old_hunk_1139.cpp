{
  printf("Would you like to see advanced options? [No]:");
  char buffer[4096];
  if(!fgets(buffer, sizeof(buffer)-1, stdin))
    {
    buffer[0] = 0;
    }