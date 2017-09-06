void DumpExternalsObjects() {
    unsigned i;
    PSTR stringTable;
    std::string symbol;
    DWORD SectChar;
    /*
     * The string table apparently starts right after the symbol table
     */
    stringTable = (PSTR)&this->SymbolTable[this->SymbolCount];
    SymbolTableType* pSymbolTable = this->SymbolTable;
    for ( i=0; i < this->SymbolCount; i++ ) {
      if (pSymbolTable->SectionNumber > 0 &&
          ( pSymbolTable->Type == 0x20 || pSymbolTable->Type == 0x0)) {
         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
            /*
            *    The name of the Function entry points
            */
            if (pSymbolTable->N.Name.Short != 0) {
               symbol = "";
               symbol.insert(0, (const char *)pSymbolTable->N.ShortName, 8);
            } else {
               symbol = stringTable + pSymbolTable->N.Name.Long;
            }

            // clear out any leading spaces
            while (isspace(symbol[0])) symbol.erase(0,1);
            // if it starts with _ and has an @ then it is a __cdecl
            // so remove the @ stuff for the export
            if(symbol[0] == '_') {
               std::string::size_type posAt = symbol.find('@');
               if (posAt != std::string::npos) {
                  symbol.erase(posAt);
               }
            }
            if (symbol[0] == '_') symbol.erase(0,1);
            if (this->ImportFlag) {
               this->ImportFlag = false;
               fprintf(this->FileOut,"EXPORTS \n");
            }
            /*
            Check whether it is "Scalar deleting destructor" and
            "Vector deleting destructor"
            */
            const char *scalarPrefix = "??_G";
            const char *vectorPrefix = "??_E";
            // original code had a check for
            // symbol.find("real@") == std::string::npos)
            // but if this disallows memmber functions with the name real
            // if scalarPrefix and vectorPrefix are not found then print
            // the symbol
            if (symbol.compare(0, 4, scalarPrefix) &&
                symbol.compare(0, 4, vectorPrefix) )
            {
               SectChar =
                 this->
                 SectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;
               if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {
                  // Read only (i.e. constants) must be excluded
                  fprintf(this->FileOut, "\t%s \t DATA\n", symbol.c_str());
               } else {
                  if ( pSymbolTable->Type  ||
                       !(SectChar & IMAGE_SCN_MEM_READ)) {
                     fprintf(this->FileOut, "\t%s\n", symbol.c_str());
                  } else {
                     // printf(" strange symbol: %s \n",symbol.c_str());
                  }
               }
            }
         }
      }
      else if (pSymbolTable->SectionNumber == IMAGE_SYM_UNDEFINED &&
               !pSymbolTable->Type && 0) {
         /*
         *    The IMPORT global variable entry points
         */
         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {
            symbol = stringTable + pSymbolTable->N.Name.Long;
            while (isspace(symbol[0]))  symbol.erase(0,1);
            if (symbol[0] == '_') symbol.erase(0,1);
            if (!this->ImportFlag) {
               this->ImportFlag = true;
               fprintf(this->FileOut,"IMPORTS \n");
            }
            fprintf(this->FileOut, "\t%s DATA \n", symbol.c_str()+1);
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