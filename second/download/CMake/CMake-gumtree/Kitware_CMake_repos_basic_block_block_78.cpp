{
      *New_Field        = *_nc_Default_Field;
      New_Field->frow   = frow;
      New_Field->fcol   = fcol;
      New_Field->link   = field->link;
      field->link       = New_Field;
      New_Field->buf    = field->buf;
      New_Field->rows   = field->rows;
      New_Field->cols   = field->cols;
      New_Field->nrow   = field->nrow;
      New_Field->nbuf   = field->nbuf;
      New_Field->drows  = field->drows;
      New_Field->dcols  = field->dcols;
      New_Field->maxgrow= field->maxgrow;
      New_Field->just   = field->just;
      New_Field->fore   = field->fore;
      New_Field->back   = field->back;
      New_Field->pad    = field->pad;
      New_Field->opts   = field->opts;
      New_Field->usrptr = field->usrptr;
      if (_nc_Copy_Type(New_Field,field)) 
	return New_Field;
    }