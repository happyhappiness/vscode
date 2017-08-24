(pos < field->drows)
	    {
	      cursor_moved = TRUE;
	      wmove(form->w,pos,0);
	      pos++;
	      winnstr(form->w,bp,field->cols);
	      found_content = 
		After_Last_Non_Pad_Position(bp,field->cols,field->pad);
	      if (found_content!=bp)
		{
		  result = TRUE;
		  break;
		}
	    }