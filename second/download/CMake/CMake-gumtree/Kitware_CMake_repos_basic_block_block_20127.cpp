(size) {
                  long_filenamew[size] = '\0';
                } else {
                  uv__free(long_filenamew);
                  long_filenamew = NULL;
                }