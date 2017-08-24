      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

   if (hFile == INVALID_HANDLE_VALUE) {
      fprintf(stderr, "Couldn't open file with CreateFile()\n");
      return;
   }

   hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
   if (hFileMapping == 0) {
      CloseHandle(hFile);
      fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");
      return;
   }

   lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
   if (lpFileBase == 0) {
      CloseHandle(hFileMapping);
      CloseHandle(hFile);
      fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");
      return;
   }

   dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
   if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
      fprintf(stderr, "File is an executable.  I don't dump those.\n");
      return;
   }
   /* Does it look like a i386 COFF OBJ file??? */
   else if (
