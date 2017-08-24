{
  FIELD *linked_field;
  int res = E_OK;
  int syncres;

  if (!field)
    return(E_BAD_ARGUMENT);

  if (!field->link)
    return(E_SYSTEM_ERROR);

  for(linked_field = field->link; 
      linked_field!= field;
      linked_field = linked_field->link )
    {
      if (((syncres=Synchronize_Field(linked_field)) != E_OK) &&
          (res==E_OK))
        res = syncres;
    }
  return(res);
}