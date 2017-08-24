{
#if GROW_IF_NAVIGATE
      FIELD *field = form->current;
      if (Single_Line_Field(field) && Field_Grown(field,1))
        return(E_OK);
#endif
      --(form->curcol);
      return(E_REQUEST_DENIED);
    }