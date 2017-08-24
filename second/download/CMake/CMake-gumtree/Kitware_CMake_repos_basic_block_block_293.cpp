(Last_Row && 
          (!(Growable(field) && !Single_Line_Field(field))))
        {
          if (!(form->opts & O_NL_OVERLOAD))
            return(E_REQUEST_DENIED);
          wclrtoeol(form->w);
          /* we have to set this here, although it is also
             handled in the generic routine. The reason is,
             that FN_Next_Field may fail, but the form is
             definitively changed */
          form->status |= _WINDOW_MODIFIED