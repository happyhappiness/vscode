{
      FIELD *field;

      field = form->current;
      if (!Single_Line_Field(field))
	{
	  result = (form->toprow==0) ? FALSE : TRUE;
	}
      else
	{
	  result = (form->begincol==0) ? FALSE : TRUE;
	}
    }