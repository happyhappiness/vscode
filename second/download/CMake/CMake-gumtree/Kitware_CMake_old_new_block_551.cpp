{
      CloseHandle(hFileMapping);
      CloseHandle(hFile);
      fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");
      return;
   }