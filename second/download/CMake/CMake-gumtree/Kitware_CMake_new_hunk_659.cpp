      * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;

      */

      DumpSymbols<IMAGE_FILE_HEADER, IMAGE_SYMBOL>

        symbolDumper((PIMAGE_FILE_HEADER) lpFileBase, fout,

                     (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));

      symbolDumper.DumpObjFile();

   } else {

      // check for /bigobj format

      cmANON_OBJECT_HEADER_BIGOBJ* h =

        (cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase;

      if(h->Sig1 == 0x0 && h->Sig2 == 0xffff) {

         DumpSymbols<cmANON_OBJECT_HEADER_BIGOBJ, cmIMAGE_SYMBOL_EX>

           symbolDumper((cmANON_OBJECT_HEADER_BIGOBJ*) lpFileBase, fout,

                        (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64));

         symbolDumper.DumpObjFile();

      } else {

         printf("unrecognized file format in '%s'\n", filename);
