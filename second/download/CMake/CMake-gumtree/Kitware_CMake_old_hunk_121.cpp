      pSymbolTable++;

    }

  }

private:

  std::set<std::string>& Symbols;

  std::set<std::string>& DataSymbols;

  DWORD_PTR SymbolCount;

  PIMAGE_SECTION_HEADER SectionHeaders;

  ObjectHeaderType* ObjectImageHeader;

  SymbolTableType*  SymbolTable;

  bool Is64Bit;

};



bool

DumpFile(const char* filename,

         std::set<std::string>& symbols,

         std::set<std::string>& dataSymbols)

{

   HANDLE hFile;

   HANDLE hFileMapping;

   LPVOID lpFileBase;

   PIMAGE_DOS_HEADER dosHeader;



   hFile = CreateFileW(cmsys::Encoding::ToWide(filename).c_str(),

                       GENERIC_READ, FILE_SHARE_READ, NULL,

      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);



   if (hFile == INVALID_HANDLE_VALUE) {

      fprintf(stderr, "Couldn't open file '%s' with CreateFile()\n", filename);

      return false;

   }



   hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

   if (hFileMapping == 0) {

      CloseHandle(hFile);

      fprintf(stderr, "Couldn't open file mapping with CreateFileMapping()\n");

      return false;

   }



   lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);

   if (lpFileBase == 0) {

      CloseHandle(hFileMapping);

      CloseHandle(hFile);

      fprintf(stderr, "Couldn't map view of file with MapViewOfFile()\n");

      return false;

   }



   dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;

   if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {

      fprintf(stderr, "File is an executable.  I don't dump those.\n");

      return false;

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

      DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>

        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, symbols, dataSymbols,

                     (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));

      symbolDumper.DumpObjFile();

   } else {

      // check for /bigobj format

      cmANON_OBJECT_HEADER_BIGOBJ* h =

        (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;

      if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {

         DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>

           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, symbols,

                        dataSymbols,

                        (h->Machine == IMAGE_FILE_MACHINE_AMD64));

         symbolDumper.DumpObjFile();

      } else {

         printf("unrecognized file format in '%s'\n", filename);

         return false;

      }

   }

   UnmapViewOfFile(lpFileBase);

   CloseHandle(hFileMapping);

   CloseHandle(hFile);

   return true;

}



bool bindexplib::AddObjectFile(const char* filename)

