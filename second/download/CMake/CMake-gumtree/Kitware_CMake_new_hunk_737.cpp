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

