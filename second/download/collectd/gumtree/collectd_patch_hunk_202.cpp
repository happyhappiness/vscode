 			close (fd);
 			break;
 		}
 
 		if (strcasecmp (fields[0], "getval") == 0)
 		{
-			us_handle_getval (fhout, fields, fields_num);
+			handle_getval (fhout, fields, fields_num);
 		}
 		else if (strcasecmp (fields[0], "putval") == 0)
 		{
 			handle_putval (fhout, fields, fields_num);
 		}
 		else if (strcasecmp (fields[0], "listval") == 0)
 		{
-			us_handle_listval (fhout, fields, fields_num);
+			handle_listval (fhout, fields, fields_num);
 		}
 		else if (strcasecmp (fields[0], "putnotif") == 0)
 		{
 			handle_putnotif (fhout, fields, fields_num);
 		}
+		else if (strcasecmp (fields[0], "flush") == 0)
+		{
+			handle_flush (fhout, fields, fields_num);
+		}
 		else
 		{
-			fprintf (fhout, "-1 Unknown command: %s\n", fields[0]);
-			fflush (fhout);
+			if (fprintf (fhout, "-1 Unknown command: %s\n", fields[0]) < 0)
+			{
+				char errbuf[1024];
+				WARNING ("unixsock plugin: failed to write to socket #%i: %s",
+						fileno (fhout),
+						sstrerror (errno, errbuf, sizeof (errbuf)));
+				break;
+			}
 		}
 	} /* while (fgets) */
 
 	DEBUG ("Exiting..");
 	fclose (fhin);
 	fclose (fhout);
