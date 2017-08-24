{ /* the field becomes now static */
          field->status &= ~_MAY_GROW;
          /* if actually we have no hidden columns, justification may
             occur again */
          if (single_line_field                 &&
              (field->cols == field->dcols)     &&
              (field->just != NO_JUSTIFICATION) &&
              Field_Really_Appears(field))
            {
              res2 = Display_Field(field);
            }
        }