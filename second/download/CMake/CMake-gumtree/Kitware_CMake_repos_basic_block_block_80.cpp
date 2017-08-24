((maxgrow==0) ||
	      ( single_line_field && (field->dcols < maxgrow)) ||
	      (!single_line_field && (field->drows < maxgrow)))
	    field->status |= _MAY_GROW