{
	      check_len = field->dcols - pos;
	      if ( check_len >= field->cols )
		check_len = field->cols;
	      cursor_moved = TRUE;
	      wmove(form->w,0,pos);
	      winnstr(form->w,bp,check_len);
	      found_content = 
		After_Last_Non_Pad_Position(bp,check_len,field->pad);
	      if (found_content==bp)
		  pos += field->cols;		  
	      else
		{
		  result = TRUE;
		  break;
		}
	    }