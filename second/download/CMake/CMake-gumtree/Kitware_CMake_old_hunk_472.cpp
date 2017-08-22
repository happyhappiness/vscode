                  symbol.erase(posAt);
               }
            }
            if (symbol[0] == '_') symbol.erase(0,1);
            if (this->ImportFlag) {
               this->ImportFlag = false;
               fprintf(this->FileOut,"EXPORTS \n");
