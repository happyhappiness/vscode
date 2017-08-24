{
  FIELD *field = form->current;
  
  if ((++(form->curcol))==field->dcols)
    {
      if ((++(form->currow))==field->drows)
        {
#if GROW_IF_NAVIGATE
          if (!Single_Line_Field(field) && Field_Grown(field,1)) {
            form->curcol = 0;
            return(E_OK);
          }
#endif
          form->currow--;
#if GROW_IF_NAVIGATE
          if (Single_Line_Field(field) && Field_Grown(field,1))
            return(E_OK);
#endif
          form->curcol--;
          return(E_REQUEST_DENIED);
        }
      form->curcol = 0;
    }
  return(E_OK);
}