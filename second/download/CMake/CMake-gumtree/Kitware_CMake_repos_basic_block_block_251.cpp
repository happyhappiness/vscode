{
  if ( (--(form->currow)) < 0 )
    {
      form->currow++;
      return(E_REQUEST_DENIED);
    }
  form->curcol = 0;
  return(E_OK);
}