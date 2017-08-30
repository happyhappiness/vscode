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
