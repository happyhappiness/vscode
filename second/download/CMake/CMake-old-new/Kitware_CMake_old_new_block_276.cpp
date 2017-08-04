{
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