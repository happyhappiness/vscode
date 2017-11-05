static void
find_variables (const char *string,
		void (*callback) (const char *var_ptr, size_t var_len))
{
  for (; *string != '\0';)
    if (*string++ == '$')
      {
	const char *variable_start;
	const char *variable_end;
	unsigned short int valid;
	char c;

	if (*string == '{')
	  string++;

	variable_start = string;
	c = *string;
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
	  {
	    do
	      c = *++string;
	    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		   || (c >= '0' && c <= '9') || c == '_');
	    variable_end = string;

	    if (variable_start[-1] == '{')
	      {
		if (*string == '}')
		  {
		    string++;
		    valid = 1;
		  }
		else
		  valid = 0;
	      }
	    else
	      valid = 1;

	    if (valid)
	      callback (variable_start, variable_end - variable_start);
	  }
      }
}