               }
            }
            if (symbol[0] == '_') symbol.erase(0,1);
            if (fImportFlag) {
               fImportFlag = 0;
               fprintf(fout,"EXPORTS \n");
            }
            /*
            Check whether it is "Scalar deleting destructor" and
