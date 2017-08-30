  printf("Current Value: %s\n", iter.GetValue());

  printf("New Value (Enter to keep current value): ");

  char buffer[4096];

  if(!fgets(buffer, sizeof(buffer)-1, stdin))

    {

    buffer[0] = 0;

    }

