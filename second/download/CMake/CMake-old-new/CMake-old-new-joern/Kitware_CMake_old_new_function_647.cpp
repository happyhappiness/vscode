void
DumpExternals(PIMAGE_SYMBOL pSymbolTable, FILE *fout, unsigned cSymbols)
{
   unsigned i;
   PSTR stringTable;
   std::string symbol;

   /*
   * The string table apparently starts right after the symbol table
   */
   stringTable = (PSTR)&pSymbolTable[cSymbols];

   for ( i=0; i < cSymbols; i++ ) {
      if (pSymbolTable->SectionNumber > 0 && pSymbolTable->Type == 0x20) {
         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
            if (pSymbolTable->N.Name.Short != 0) {
               symbol = "";
               symbol.insert(0, (const char *)(pSymbolTable->N.ShortName), 8);
            } else {
               symbol = stringTable + pSymbolTable->N.Name.Long;
            }
            std::string::size_type posAt = symbol.find('@');
            if (posAt != std::string::npos) symbol.erase(posAt);
#ifndef _MSC_VER
            fprintf(fout, "\t%s\n", symbol.c_str());
#else
            fprintf(fout, "\t%s\n", symbol.c_str()+1);
#endif
         }
      }

      /*
      * Take into account any aux symbols
      */
      i += pSymbolTable->NumberOfAuxSymbols;
      pSymbolTable += pSymbolTable->NumberOfAuxSymbols;
      pSymbolTable++;
   }
}