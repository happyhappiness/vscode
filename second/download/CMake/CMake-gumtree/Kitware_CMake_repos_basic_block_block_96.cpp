(field->pad != ch)
	{
	  field->pad = ch;
	  res = _nc_Synchronize_Attributes( field );
	}
      else
	res = E_OK