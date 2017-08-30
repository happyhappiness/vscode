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
