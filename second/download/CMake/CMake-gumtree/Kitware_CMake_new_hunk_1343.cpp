  result = 0;

  }

# endif

# ifdef DIRECTORY_DEF_DEBUG

  {

  fprintf(stderr, "DIRECTORY_DEF_DEBUG should not be defined in C\n");

  result = 0;

  }

# endif

# ifndef FILE_DEF_RELEASE

#  ifndef PREPROCESS_XCODE

  {

