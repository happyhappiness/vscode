{
	  size_t len;

	  len = Total_Buffer_Size(New_Field);
	  if ( (New_Field->buf=(char *)malloc(len)) )
	    {
	      memcpy(New_Field->buf,field->buf,len);
	      return New_Field;
	    }
	}