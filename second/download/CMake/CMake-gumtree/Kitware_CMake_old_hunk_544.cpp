            symbol = stringTable + pSymbolTable->N.Name.Long;
            while (isspace(symbol[0]))  symbol.erase(0,1);
            if (symbol[0] == '_') symbol.erase(0,1);
            if (!fImportFlag) {
               fImportFlag = 1;
               fprintf(fout,"IMPORTS \n");
            }
            fprintf(fout, "\t%s DATA \n", symbol.c_str()+1);
         }
      }

