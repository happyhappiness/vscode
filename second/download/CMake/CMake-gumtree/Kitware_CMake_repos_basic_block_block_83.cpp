{
      bool single_line_field = Single_Line_Field(field);

      if (maxgrow>0)
	{
	  if (( single_line_field && (maxgrow < field->dcols)) ||
	      (!single_line_field && (maxgrow < field->drows)))
	    RETURN(E_BAD_ARGUMENT);
	}
      field->maxgrow = maxgrow;
      field->status &= ~_MAY_GROW;
      if (!(field->opts & O_STATIC))
	{
	  if ((maxgrow==0) ||
	      ( single_line_field && (field->dcols < maxgrow)) ||
	      (!single_line_field && (field->drows < maxgrow)))
	    field->status |= _MAY_GROW;
	}
    }