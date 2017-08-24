{
      *New_Field         = *_nc_Default_Field;
      New_Field->frow    = frow;
      New_Field->fcol    = fcol;
      New_Field->link    = New_Field;
      New_Field->rows    = field->rows;
      New_Field->cols    = field->cols;
      New_Field->nrow    = field->nrow;
      New_Field->drows   = field->drows;
      New_Field->dcols   = field->dcols;
      New_Field->maxgrow = field->maxgrow;
      New_Field->nbuf    = field->nbuf;
      New_Field->just    = field->just;
      New_Field->fore    = field->fore;
      New_Field->back    = field->back;
      New_Field->pad     = field->pad;
      New_Field->opts    = field->opts;
      New_Field->usrptr  = field->usrptr;

      if (_nc_Copy_Type(New_Field,field))
	{
	  size_t len;

	  len = Total_Buffer_Size(New_Field);
	  if ( (New_Field->buf=(char *)malloc(len)) )
	    {
	      memcpy(New_Field->buf,field->buf,len);
	      return New_Field;
	    }
	}
    }