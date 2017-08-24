{
      bool single_line_field = Single_Line_Field(field);
      int res2 = E_OK;

      if (newopts & O_STATIC)
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
      else
        { /* field is no longer static */
          if ((field->maxgrow==0) ||
              ( single_line_field && (field->dcols < field->maxgrow)) ||
              (!single_line_field && (field->drows < field->maxgrow)))
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
        }
      if (res2 != E_OK)
        res = res2;
    }