{
        fprintf(stdout, "LockResource worked\n");
        char* str = (char*)malloc(datasize + 4);
        if (str) {
          memcpy(str, data, datasize);
          str[datasize] = 'E';
          str[datasize + 1] = 'O';
          str[datasize + 2] = 'R';
          str[datasize + 3] = 0;
          fprintf(stdout, "str='%s'\n", str);
          free(str);

          ret = 0;

#ifdef CMAKE_RCDEFINE_NO_QUOTED_STRINGS
          fprintf(stdout, "LoadString skipped\n");
#else
          char buf[256];
          if (::LoadString(NULL, 1026, buf, sizeof(buf)) > 0) {
            fprintf(stdout, "LoadString worked\n");
            fprintf(stdout, "buf='%s'\n", buf);
          } else {
            fprintf(stdout, "LoadString failed\n");
            ret = 1;
          }
#endif
        }
      }