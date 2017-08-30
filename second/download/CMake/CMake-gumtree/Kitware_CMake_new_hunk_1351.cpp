  result = 0;
  }
# endif
# ifdef DIRECTORY_DEF_RELEASE
  {
  fprintf(stderr, "DIRECTORY_DEF_RELEASE should not be defined in CXX\n");
  result = 0;
  }
# endif
#endif
#if defined(FILE_DEF_DEBUG) || defined(TARGET_DEF_DEBUG)
# if !defined(FILE_DEF_DEBUG) || !defined(TARGET_DEF_DEBUG)
