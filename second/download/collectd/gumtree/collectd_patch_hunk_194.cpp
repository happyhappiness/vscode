 	{
 		fprintf (stderr, "connect failed: %s\n",
 				strerror (errno));
 		return (-1);
 	}
 
-	fh = fdopen (fd, "r+");
-	if (fh == NULL)
+	fh_in = fdopen (fd, "r");
+	if (fh_in == NULL)
 	{
 		fprintf (stderr, "fdopen failed: %s\n",
 				strerror (errno));
 		close (fd);
 		return (-1);
 	}
 
-	fprintf (fh, "GETVAL %s/%s\n", hostname_g, value_string_g);
-	fflush (fh);
+	fh_out = fdopen (fd, "w");
+	if (fh_out == NULL)
+	{
+		fprintf (stderr, "fdopen failed: %s\n",
+				strerror (errno));
+		fclose (fh_in);
+		return (-1);
+	}
+
+	fprintf (fh_out, "GETVAL %s/%s\n", hostname_g, value_string_g);
+	fflush (fh_out);
 
-	if (fgets (buffer, sizeof (buffer), fh) == NULL)
+	if (fgets (buffer, sizeof (buffer), fh_in) == NULL)
 	{
 		fprintf (stderr, "fgets failed: %s\n",
 				strerror (errno));
-		close (fd);
+		fclose (fh_in);
+		fclose (fh_out);
 		return (-1);
 	}
-	close (fd); fd = -1;
+	fclose (fh_in); fh_in = NULL; fd = -1;
+	fclose (fh_out); fh_out = NULL;
 
 	values_num = atoi (buffer);
 	if (values_num < 1)
 		return (-1);
 
 	values = (double *) malloc (values_num * sizeof (double));
