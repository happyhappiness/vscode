{
	  val = atof(s);
	  if (low<high)
	    {
	      if (val<low || val>high) return FALSE;
	    }
	  sprintf(buf,"%.*f",(prec>0?prec:0),val);
	  set_field_buffer(field,0,buf);
	  return TRUE;
	}