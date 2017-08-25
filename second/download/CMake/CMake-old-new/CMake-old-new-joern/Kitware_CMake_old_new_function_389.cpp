void
DumpFile(const char* filename, FILE *fout)
{
   HANDLE hFile;
   HANDLE hFileMapping;
   LPVOID lpFileBase;
   PIMAGE_DOS_HEADER dosHeader;

   hFile = CreateFileW(cmsys::Encoding::ToWide(filename).c_str(),
                       GENERIC_READ, FILE_SHARE_READ, NULL,
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
           ((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||
            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64))
           && (dosHeader->e_sp == 0)
           ) {
      /*
      * The two tests above aren't what they look like.  They're
      * really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C)
      * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;
      */
      DumpObjFile((PIMAGE_FILE_HEADER) lpFileBase, fout);
   } else {
      printf("unrecognized file format in '%s'\n", filename);
      return false;
   }
   UnmapViewOfFile(lpFileBase);
   CloseHandle(hFileMapping);
   CloseHandle(hFile);
   return true;
}