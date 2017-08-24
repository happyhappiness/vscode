{
      strncpy(buf,str,sizeof(buf));
      while( (i<sizeof(buf)) && (buf[i] != '\0') )
	{
	  buf[i] = toupper((int)(buf[i]));
	  i++;
	}
      
      for (i=0; i < A_SIZE; i++)
	{
	  if (strncmp(request_names[i],buf,sizeof(buf))==0)
	    return MIN_FORM_COMMAND + i;
	} 
    }