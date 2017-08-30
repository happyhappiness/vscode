                 SectionHeaders[pSymbolTable->SectionNumber-1].Characteristics;

               if (!pSymbolTable->Type  && (SectChar & IMAGE_SCN_MEM_WRITE)) {

                  // Read only (i.e. constants) must be excluded

                  this->DataSymbols.insert(symbol);

               } else {

                  if ( pSymbolTable->Type  ||

                       !(SectChar & IMAGE_SCN_MEM_READ)) {

                     this->Symbols.insert(symbol);

                  } else {

                     // printf(" strange symbol: %s \n",symbol.c_str());

                  }

