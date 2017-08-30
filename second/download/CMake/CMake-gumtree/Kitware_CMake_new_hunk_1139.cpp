{

  printf("Would you like to see advanced options? [No]:");

  char buffer[4096];

  if(!fgets(buffer, static_cast<int>(sizeof(buffer) - 1), stdin))

    {

    buffer[0] = 0;

    }
