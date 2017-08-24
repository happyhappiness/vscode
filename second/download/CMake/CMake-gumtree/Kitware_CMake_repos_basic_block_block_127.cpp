{
      if (j==0) 
	pg->pmin = j;
      else
	{
	  if (fields[j]->status & _NEWPAGE)
	    {
	      pg->pmax = j-1;
	      pg++;
	      pg->pmin = j;
	    }
	}
      
      maximum_row_in_field = fields[j]->frow + fields[j]->rows;
      maximum_col_in_field = fields[j]->fcol + fields[j]->cols;
      
      if (form->rows < maximum_row_in_field) 
	form->rows = maximum_row_in_field;
      if (form->cols < maximum_col_in_field) 
	form->cols = maximum_col_in_field;
    }