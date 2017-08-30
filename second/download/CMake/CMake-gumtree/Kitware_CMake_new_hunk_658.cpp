                  symbol.erase(posAt);

               }

            }

            // For 64 bit builds we don't need to remove _

            if(!this->Is64Bit)

              {

              if (symbol[0] == '_')

                {

                symbol.erase(0,1);

                }

              }

            if (this->ImportFlag) {

               this->ImportFlag = false;

               fprintf(this->FileOut,"EXPORTS \n");

