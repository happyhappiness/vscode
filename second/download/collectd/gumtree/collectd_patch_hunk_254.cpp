 				&& ((buffer[len - 1] == '\n') || (buffer[len - 1] == '\r')))
 			buffer[--len] = '\0';
 
 		if (len == 0)
 			continue;
 
-		DEBUG ("fgets -> buffer = %s; len = %i;", buffer, len);
+		sstrncpy (buffer_copy, buffer, sizeof (buffer_copy));
 
-		fields_num = strsplit (buffer, fields,
+		fields_num = strsplit (buffer_copy, fields,
 				sizeof (fields) / sizeof (fields[0]));
 
 		if (fields_num < 1)
 		{
 			close (fd);
 			break;
 		}
 
 		if (strcasecmp (fields[0], "getval") == 0)
 		{
-			handle_getval (fhout, fields, fields_num);
+			handle_getval (fhout, buffer);
 		}
 		else if (strcasecmp (fields[0], "putval") == 0)
 		{
-			handle_putval (fhout, fields, fields_num);
+			handle_putval (fhout, buffer);
 		}
 		else if (strcasecmp (fields[0], "listval") == 0)
 		{
-			handle_listval (fhout, fields, fields_num);
+			handle_listval (fhout, buffer);
 		}
 		else if (strcasecmp (fields[0], "putnotif") == 0)
 		{
-			handle_putnotif (fhout, fields, fields_num);
+			handle_putnotif (fhout, buffer);
 		}
 		else if (strcasecmp (fields[0], "flush") == 0)
 		{
-			handle_flush (fhout, fields, fields_num);
+			handle_flush (fhout, buffer);
 		}
 		else
 		{
 			if (fprintf (fhout, "-1 Unknown command: %s\n", fields[0]) < 0)
 			{
 				char errbuf[1024];
