  result = 0;

  }

# endif

# ifndef DIRECTORY_DEF_RELEASE

  {

  fprintf(stderr, "DIRECTORY_DEF_RELEASE should be defined in C\n");

  result = 0;

  }

# endif

#endif

#ifdef PREPROCESS_DEBUG

# ifndef FILE_DEF_DEBUG

