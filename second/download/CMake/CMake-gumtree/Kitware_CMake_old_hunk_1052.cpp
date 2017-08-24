  printf("Current Value: %s\n", iter.GetValue());
  printf("New Value (Enter to keep current value): ");
  char buffer[4096];
  buffer[0] = 0;
  (void) fgets(buffer, sizeof(buffer)-1, stdin);

  if(strlen(buffer) > 0)
    {
