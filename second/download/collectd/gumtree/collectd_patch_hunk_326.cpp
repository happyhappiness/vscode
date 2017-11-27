 			continue;
 
 		sstrncpy (buffer_copy, buffer, sizeof (buffer_copy));
 
 		fields_num = strsplit (buffer_copy, fields,
 				sizeof (fields) / sizeof (fields[0]));
-
 		if (fields_num < 1)
 		{
-			close (fd);
-			break;
+			fprintf (fhout, "-1 Internal error\n");
+			fclose (fhin);
+			fclose (fhout);
+			pthread_exit ((void *) 1);
 		}
 
 		if (strcasecmp (fields[0], "getval") == 0)
 		{
 			handle_getval (fhout, buffer);
 		}
