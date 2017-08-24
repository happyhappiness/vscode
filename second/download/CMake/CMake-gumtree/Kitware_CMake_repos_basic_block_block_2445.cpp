{
    test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);
    if (partial_match != 0 && strstr(test_name, arg) != NULL) { /* NOLINT */
      testToRun = i;
      ac -= 2;
      av += 2;
    } else if (partial_match == 0 && strcmp(test_name, arg) == 0) {
      testToRun = i;
      ac--;
      av++;
    }
    free(test_name);
  }