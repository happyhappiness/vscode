(End_Of_Field && !Growable(field) && (field->opts & O_AUTOSKIP))
            result = Inter_Field_Navigation(FN_Next_Field,form);
          else
            {
              if (End_Of_Field && Growable(field) && !Field_Grown(field,1))
                result = E_SYSTEM_ERROR;
              else
                {
                  IFN_Next_Character(form);
                  result = E_OK;
                }
            }