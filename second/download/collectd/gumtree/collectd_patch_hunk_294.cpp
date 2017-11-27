 
 	DEBUG ("csv plugin: csv_write: filename = %s;", filename);
 
 	if (value_list_to_string (values, sizeof (values), ds, vl) != 0)
 		return (-1);
 
+	if (use_stdio)
+	{
+		size_t i;
+
+		escape_string (filename, sizeof (filename));
+
+		/* Replace commas by colons for PUTVAL compatible output. */
+		for (i = 0; i < sizeof (values); i++)
+		{
+			if (values[i] == 0)
+				break;
+			else if (values[i] == ',')
+				values[i] = ':';
+		}
+
+		fprintf (use_stdio == 1 ? stdout : stderr,
+			 "PUTVAL %s interval=%i %s\n",
+			 filename, interval_g, values);
+		return (0);
+	}
+
 	if (stat (filename, &statbuf) == -1)
 	{
 		if (errno == ENOENT)
 		{
 			if (csv_create_file (filename, ds))
 				return (-1);
