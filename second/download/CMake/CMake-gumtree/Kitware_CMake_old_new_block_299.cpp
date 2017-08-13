{
   unsigned i;
   PSTR stringTable;
   std::string sectionName;
   std::string sectionCharacter;
   int iSectNum;

   fprintf(fout, "Symbol Table - %X entries  (* = auxillary symbol)\n",
      cSymbols);

   fprintf(fout,
      "Indx Name                 Value    Section    cAux  Type    Storage  Character\n"
      "---- -------------------- -------- ---------- ----- ------- -------- ---------\n");

   /*
   * The string table apparently starts right after the symbol table
   */
   stringTable = (PSTR)&pSymbolTable[cSymbols];

   for ( i=0; i < cSymbols; i++ ) {
      fprintf(fout, "%04X ", i);
      if ( pSymbolTable->N.Name.Short != 0 )
         fprintf(fout, "%-20.8s", pSymbolTable->N.ShortName);
      else
         fprintf(fout, "%-20s", stringTable + pSymbolTable->N.Name.Long);

      fprintf(fout, " %08X", pSymbolTable->Value);

      iSectNum = pSymbolTable->SectionNumber;
      GetSectionName(pSymbolTable, sectionName);
      fprintf(fout, " sect:%s aux:%X type:%02X st:%s",
         sectionName.c_str(),
         pSymbolTable->NumberOfAuxSymbols,
         pSymbolTable->Type,
         GetSZStorageClass(pSymbolTable->StorageClass) );

      GetSectionCharacteristics(pSectionHeaders,iSectNum,sectionCharacter);
      fprintf(fout," hc: %s \n",sectionCharacter.c_str());
#if 0
      if ( pSymbolTable->NumberOfAuxSymbols )
         DumpAuxSymbols(pSymbolTable);
#endif

      /*
      * Take into account any aux symbols
      */
      i += pSymbolTable->NumberOfAuxSymbols;
      pSymbolTable += pSymbolTable->NumberOfAuxSymbols;
      pSymbolTable++;
   }
}