r(j = form->page[page_nr].pmin;j <= form->page[page_nr].pmax;j++)
	{
	  fields[j]->index = j;
	  fields[j]->page  = page_nr;
	  fld = Insert_Field_By_Position(fields[j],fld);
	}