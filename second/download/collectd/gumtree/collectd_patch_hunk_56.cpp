 			total += values[i];
 			total_num++;
 		}
 	}
 
 	if (total_num == 0)
-	{
-		printf ("WARNING: No defined values found\n");
+		average = NAN;
+	else
+		average = total / total_num;
+	printf ("%lf average |", average);
+	for (i = 0; i < values_num; i++)
+		printf (" %s=%lf;;;;", values_names[i], values[i]);
+
+	if (total_num == 0)
 		return (RET_WARNING);
-	}
 
-	if (match_range (&range_critical_g, total / total_num) != 0)
-	{
-		printf ("CRITICAL: Average = %lf\n",
-				(double) (total / total_num));
+	if (isnan (average)
+			|| match_range (&range_critical_g, average))
 		return (RET_CRITICAL);
-	}
-	else if (match_range (&range_warning_g, total / total_num) != 0)
-	{
-		printf ("WARNING: Average = %lf\n",
-				(double) (total / total_num));
+	else if (match_range (&range_warning_g, average) != 0)
 		return (RET_WARNING);
-	}
-	else
-	{
-		printf ("OKAY: Average = %lf\n",
-				(double) (total / total_num));
-		return (RET_OKAY);
-	}
 
-	return (RET_UNKNOWN);
+	return (RET_OKAY);
 } /* int do_check_con_average */
 
 int do_check_con_sum (int values_num, double *values, char **values_names)
 {
 	int i;
 	double total;
