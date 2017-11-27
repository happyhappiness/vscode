 			total += values[i];
 			total_num++;
 		}
 	}
 
 	if (total_num == 0)
-		average = NAN;
-	else
-		average = total / total_num;
-	printf ("%lf average |", average);
-	for (i = 0; i < values_num; i++)
-		printf (" %s=%lf;;;;", values_names[i], values[i]);
-
-	if (total_num == 0)
+	{
+		printf ("WARNING: No defined values found\n");
 		return (RET_WARNING);
+	}
 
-	if (isnan (average)
-			|| match_range (&range_critical_g, average))
-		return (RET_CRITICAL);
+	average = total / total_num;
+
+	if (match_range (&range_critical_g, average) != 0)
+	{
+		status_str = "CRITICAL";
+		status_code = RET_CRITICAL;
+	}
 	else if (match_range (&range_warning_g, average) != 0)
-		return (RET_WARNING);
+	{
+		status_str = "WARNING";
+		status_code = RET_WARNING;
+	}
+	else
+	{
+		status_str = "OKAY";
+		status_code = RET_OKAY;
+	}
 
-	return (RET_OKAY);
+	printf ("%s: %g average |", status_str, average);
+	for (i = 0; i < values_num; i++)
+		printf (" %s=%g;;;;", values_names[i], values[i]);
+	printf ("\n");
+
+	return (status_code);
 } /* int do_check_con_average */
 
-int do_check_con_sum (int values_num, double *values, char **values_names)
+static int do_check_con_sum (size_t values_num,
+		double *values, char **values_names)
 {
-	int i;
+	size_t i;
 	double total;
 	int total_num;
+	const char *status_str = "UNKNOWN";
+	int status_code = RET_UNKNOWN;
 
 	total = 0.0;
 	total_num = 0;
 	for (i = 0; i < values_num; i++)
 	{
 		if (!isnan (values[i]))
