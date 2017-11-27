 	{
 		fprintf (stderr, "malloc failed: %s\n",
 				strerror (errno));
 		free (values);
 		return (-1);
 	}
+	memset (values_names, 0, values_num * sizeof (char *));
 
-	i = 0;
+	i = 0; /* index of the values returned by the server */
+	j = 0; /* number of values in `values_names' and `values' */
 	while (fgets (buffer, sizeof (buffer), fh_in) != NULL)
 	{
-		char *key;
-		char *value;
-
-		key = buffer;
-
-		value = strchr (key, '=');
-		if (value == NULL)
-			continue;
-		*value = '\0'; value++;
-
-		if (ignore_ds (key) != 0)
-			continue;
-
-		values_names[i] = strdup (key);
-		values[i] = atof (value);
+		do /* while (0) */
+		{
+			char *key;
+			char *value;
+			char *endptr;
+
+			key = buffer;
+
+			value = strchr (key, '=');
+			if (value == NULL)
+			{
+				fprintf (stderr, "Cannot parse line: %s\n", buffer);
+				break;
+			}
+			*value = 0;
+			value++;
+
+			if (ignore_ds (key) != 0)
+				break;
+
+			endptr = NULL;
+			errno = 0;
+			values[j] = strtod (value, &endptr);
+			if ((endptr == value) || (errno != 0))
+			{
+				fprintf (stderr, "Could not parse buffer "
+						"as number: %s\n", value);
+				break;
+			}
+
+			values_names[j] = strdup (key);
+			if (values_names[j] == NULL)
+			{
+				fprintf (stderr, "strdup failed.\n");
+				break;
+			}
+			j++;
+		} while (0);
 
 		i++;
 		if (i >= values_num)
 			break;
 	}
-	values_num = i;
+	/* Set `values_num' to the number of values actually stored in the
+	 * array. */
+	values_num = j;
 
 	fclose (fh_in); fh_in = NULL; fd = -1;
 	fclose (fh_out); fh_out = NULL;
 
 	*ret_values_num = values_num;
 	*ret_values = values;
