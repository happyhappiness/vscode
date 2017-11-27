 		else if (match_range (&range_warning_g, values[i]) != 0)
 			num_warning++;
 		else
 			num_okay++;
 	}
 
-	printf ("%i critical, %i warning, %i okay",
+	if ((num_critical == 0) && (num_warning == 0) && (num_okay == 0))
+	{
+		printf ("WARNING: No defined values found\n");
+		return (RET_WARNING);
+	}
+	else if ((num_critical == 0) && (num_warning == 0))
+	{
+		status_str = "OKAY";
+		status_code = RET_OKAY;
+	}
+	else if (num_critical == 0)
+	{
+		status_str = "WARNING";
+		status_code = RET_WARNING;
+	}
+	else
+	{
+		status_str = "CRITICAL";
+		status_code = RET_CRITICAL;
+	}
+
+	printf ("%s: %i critical, %i warning, %i okay", status_str,
 			num_critical, num_warning, num_okay);
 	if (values_num > 0)
 	{
 		printf (" |");
 		for (i = 0; i < values_num; i++)
-			printf (" %s=%lf;;;;", values_names[i], values[i]);
+			printf (" %s=%g;;;;", values_names[i], values[i]);
 	}
 	printf ("\n");
 
-	if ((num_critical != 0) || (values_num == 0))
-		return (RET_CRITICAL);
-	else if (num_warning != 0)
-		return (RET_WARNING);
-
-	return (RET_OKAY);
+	return (status_code);
 } /* int do_check_con_none */
 
-int do_check_con_average (int values_num, double *values, char **values_names)
+static int do_check_con_average (size_t values_num,
+		double *values, char **values_names)
 {
-	int i;
+	size_t i;
 	double total;
 	int total_num;
 	double average;
+	const char *status_str = "UNKNOWN";
+	int status_code = RET_UNKNOWN;
 
 	total = 0.0;
 	total_num = 0;
 	for (i = 0; i < values_num; i++)
 	{
 		if (!isnan (values[i]))
