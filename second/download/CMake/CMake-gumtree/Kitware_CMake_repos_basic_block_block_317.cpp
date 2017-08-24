{
  FIELD *field;

  field = form->current; 
  
  Synchronize_Buffer(form);
  if ((form->status & _FCHECK_REQUIRED) ||
      (!(field->opts & O_PASSOK)))
    {
      if (!Check_Field(field->type,field,(TypeArgument *)(field->arg)))
        return FALSE;
      form->status  &= ~_FCHECK_REQUIRED;
      field->status |= _CHANGED;
      Synchronize_Linked_Fields(field);
    }
  return TRUE;
}