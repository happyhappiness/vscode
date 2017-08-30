        {
        while (bread >= 1023) 
          {
          //std::cout << "Read data..." << std::endl;
          ReadFile(read_stdout,buf,1023,&bread,NULL);
 
          //read the stdout pipe 
          std::cout << buf << std::flush;
          memset(buf, 0, sizeof(buf));
 
          }
