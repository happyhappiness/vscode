{
      *New_Field       = default_field;
      New_Field->rows  = rows;
      New_Field->cols  = cols;
      New_Field->drows = rows + nrow;
      New_Field->dcols = cols;
      New_Field->frow  = frow;
      New_Field->fcol  = fcol;
      New_Field->nrow  = nrow;
      New_Field->nbuf  = nbuf;
      New_Field->link  = New_Field;

      if (_nc_Copy_Type(New_Field,&default_field))
	{
	  size_t len;

	  len = Total_Buffer_Size(New_Field);
	  if ((New_Field->buf = (char *)malloc(len)))
	    {
	      /* Prefill buffers with blanks and insert terminating zeroes
		 between buffers */
	      int i;

	      memset(New_Field->buf,' ',len);
	      for(i=0;i<=New_Field->nbuf;i++)
		{
		  New_Field->buf[(New_Field->drows*New_Field->cols+1)*(i+1)-1]
		    = '\0';
		}
	      return New_Field;
	    }
	}
    }