{
      if (error) {
        fprintf(stderr, "%s:0:  message  [category/category] [0]\n", argv[i]);
      }
      fprintf(stdout, "Done processing %s\nTotal errors found: %i\n", argv[i],
              error);
    }