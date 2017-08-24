(vlen > len)
        {
          if (!Field_Grown(field,
                           (int)(1 + (vlen-len)/((field->rows+field->nrow)*field->cols))))
            RETURN(E_SYSTEM_ERROR);

          /* in this case we also have to check, whether or not the remaining
             characters in value are also printable for buffer 0. */
          if (buffer==0)
            {
              unsigned int i;
          
              for(i=len; i<vlen; i++)
                if (!isprint((int)(value[i])))
                  RETURN(E_BAD_ARGUMENT);
            }
          len = vlen;
        }