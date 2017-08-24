(field->just != just)
	{
	  field->just = just;
	  res = _nc_Synchronize_Attributes( field );
	}
      else
	res = E_OK