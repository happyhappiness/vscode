(End_Of_Field && Growable(field) && !Field_Grown(field,1))
                result = E_SYSTEM_ERROR;
              else
                {
                  IFN_Next_Character(form);
                  result = E_OK;
                }