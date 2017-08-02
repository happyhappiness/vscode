{
      CloseHandle(hFile);
      fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");
      return;
   }