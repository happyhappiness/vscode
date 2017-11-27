 					i, fields[i]);
 		}
 	}
 	/* Done parsing the options. */
 
 	if (i == fields_num)
-		fprintf (fh, "0 Success\n");
-	fflush (fh);
+		print_to_socket (fh, "0 Success\n");
 
 	sfree (vl.values); 
 	sfree (identifier_copy);
 
 	return (0);
 } /* int handle_putval */
