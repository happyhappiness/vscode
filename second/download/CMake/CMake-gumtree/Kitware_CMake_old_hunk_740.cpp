      */
      DumpObjFile((PIMAGE_FILE_HEADER) lpFileBase, fout);
   } else {
      printf("unrecognized file format\n");
   }
   UnmapViewOfFile(lpFileBase);
   CloseHandle(hFileMapping);
   CloseHandle(hFile);
}