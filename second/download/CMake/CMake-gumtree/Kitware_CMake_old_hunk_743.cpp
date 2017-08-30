            }



            while (isspace(symbol[0])) symbol.erase(0,1);

#ifdef _MSC_VER

            if (symbol[0] == '_') symbol.erase(0,1);

            if (fort) {

               std::string::size_type posAt = symbol.find('@');

               if (posAt != std::string::npos) symbol.erase(posAt);

            }

#endif

            if (fImportFlag) {

               fImportFlag = 0;

               fprintf(fout,"EXPORTS \n");

