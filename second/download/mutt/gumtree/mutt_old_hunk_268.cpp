  
  switch (OutputFormat)
  {
    /* configuration file */
    case F_CONF:
    {
      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH)
      {
	fprintf (out, "\n# set %s=\"", varname);
	conf_print_strval (val, out);
	fputs ("\"", out);
      }
      else if (type != DT_SYN)
	fprintf (out, "\n# set %s=%s", varname, val);
      
      fprintf (out, "\n#\n# Name: %s", varname);
      fprintf (out, "\n# Type: %s", type2human (type));
      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH)
      {
	fputs ("\n# Default: \"", out);
	conf_print_strval (val, out);
	fputs ("\"", out);
      }
      else
