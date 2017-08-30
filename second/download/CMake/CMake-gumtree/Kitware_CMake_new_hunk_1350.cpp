  result = 0;

  }

# endif

# ifndef DIRECTORY_DEF_DEBUG

  {

  fprintf(stderr, "DIRECTORY_DEF_DEBUG should be defined in CXX\n");

  result = 0;

  }

# endif

# ifdef FILE_DEF_RELEASE

  {

  fprintf(stderr, "FILE_DEF_RELEASE should not be defined in CXX\n");

