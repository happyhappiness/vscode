(!Maybe_Done && !Field_Grown(field,1))
            result = E_SYSTEM_ERROR;
          else
            {
              form->curcol = 0;
              winsertln(form->w);
              result = E_OK;
            }