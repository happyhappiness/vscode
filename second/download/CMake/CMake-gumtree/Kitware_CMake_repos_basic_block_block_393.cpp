(i=0; i < A_SIZE; i++)
	{
	  if (strncmp(request_names[i],buf,sizeof(buf))==0)
	    return MIN_FORM_COMMAND + i;
	}