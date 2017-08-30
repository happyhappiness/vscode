               }

            }

            if (symbol[0] == '_') symbol.erase(0,1);

            if (this->ImportFlag) {

               this->ImportFlag = false;

               fprintf(this->FileOut,"EXPORTS \n");

            }

            /*

            Check whether it is "Scalar deleting destructor" and

