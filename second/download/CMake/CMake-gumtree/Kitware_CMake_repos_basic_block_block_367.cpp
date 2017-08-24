{
              unsigned int i;
          
              for(i=len; i<vlen; i++)
                if (!isprint((int)(value[i])))
                  RETURN(E_BAD_ARGUMENT);
            }