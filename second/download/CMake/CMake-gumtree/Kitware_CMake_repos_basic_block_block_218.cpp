{
              field->status |= _MAY_GROW;
              /* a field with justification now changes its behaviour,
                 so we must redisplay it */
              if (single_line_field                 &&
                  (field->just != NO_JUSTIFICATION) &&
                  Field_Really_Appears(field))
                {
                  res2 = Display_Field(field);
                }        
            }