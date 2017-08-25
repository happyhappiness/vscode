{
          ReadFile(read_stdout,buf,1023,&bread,NULL); //read the stdout pipe
          printf("%s",buf);
          memset(buf, 0, sizeof(buf));
          }