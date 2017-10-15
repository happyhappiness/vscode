       sgml_id_fputs(varname, out);
       fputs ("\">\n<title>", out);
       sgml_fputs (varname, out);
       fprintf (out, "</title>\n<literallayout>Type: %s", type2human (type));
 
       
-      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH)
+      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH ||
+          type == DT_MBCHARTBL)
       {
 	if (val && *val)
 	{
 	  fputs ("\nDefault: <quote><literal>", out);
 	  sgml_print_strval (val, out);
 	  fputs ("</literal></quote>", out);
