fprintf(fout, " sect:%s aux:%X type:%02X st:%s",
         sectionName.c_str(),
         pSymbolTable->NumberOfAuxSymbols,
         pSymbolTable->Type,
         GetSZStorageClass(pSymbolTable->StorageClass) )