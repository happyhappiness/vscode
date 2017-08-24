{ /* restore to previous state */
          field->dcols = old_dcols;
          field->drows = old_drows;
          if (( single_line_field && (field->dcols!=field->maxgrow)) ||
              (!single_line_field && (field->drows!=field->maxgrow)))
            field->status |= _MAY_GROW;
          return FALSE;
        }