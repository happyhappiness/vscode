 
 	if (i == fields_num)
 		fprintf (fh, "0 Success\n");
 	fflush (fh);
 
 	sfree (vl.values); 
+	sfree (identifier_copy);
 
 	return (0);
 } /* int handle_putval */
 
