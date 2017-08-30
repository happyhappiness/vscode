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
