    fprintf(stderr, "No current working directory.\n");
    abort();
    }
  return ret;
}
inline int Chdir(const char* dir)
