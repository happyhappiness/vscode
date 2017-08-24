
bool cmakewizard::AskAdvanced()
{
  printf("Would you like to see advanced options? [No]:");  
  char buffer[4096];
  buffer[0] = 0;
  fgets(buffer, sizeof(buffer)-1, stdin);
