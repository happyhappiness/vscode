static void print_confline (const char *varname, int type, const char *val, FILE *out)
{
  if (type == DT_SYN) return;
  
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
	fprintf (out, "\n# Default: %s", val);

      fputs ("\n# ", out);
      break;
    }

    /* manual page */
    case F_MAN:
    {
      fprintf (out, "\n.TP\n.B %s\n", varname);
      fputs (".nf\n", out);
      fprintf (out, "Type: %s\n", type2human (type));
      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH)
      {
	fputs ("Default: \\(lq", out);
	man_print_strval (val, out);
	fputs ("\\(rq\n", out);
      }
      else
	fprintf (out, "Default: %s\n", val);

      fputs (".fi", out);

      break;
    }
    
    /* SGML based manual */
    case F_SGML:
    {
      fputs ("\n<sect2>", out);  sgml_fputs (varname, out);
      fprintf (out, "<label id=\"%s\">", varname);
      fprintf (out, "\n<p>\nType: %s<newline>", type2human (type));
      
      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH)
      {
	fputs ("\nDefault: &dquot;", out);
	sgml_print_strval (val, out);
	fputs ("&dquot;\n", out);
      }
      else
	fprintf (out, "\nDefault: %s\n", val);
      break;
    }
    /* make gcc happy */
    default:
      break;
  }
}