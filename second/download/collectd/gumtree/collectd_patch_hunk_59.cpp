 				datadir = NULL;
 			}
 		}
 	}
 	else if (strcasecmp ("StepSize", key) == 0)
 	{
-		int tmp = atoi (value);
-		if (tmp <= 0)
-		{
-			fprintf (stderr, "rrdtool: `StepSize' must "
-					"be greater than 0.\n");
-			return (1);
-		}
-		stepsize = tmp;
+		stepsize = atoi (value);
+		if (stepsize < 0)
+			stepsize = 0;
 	}
 	else if (strcasecmp ("HeartBeat", key) == 0)
 	{
-		int tmp = atoi (value);
-		if (tmp <= 0)
-		{
-			fprintf (stderr, "rrdtool: `HeartBeat' must "
-					"be greater than 0.\n");
-			return (1);
-		}
-		heartbeat = tmp;
+		heartbeat = atoi (value);
+		if (heartbeat < 0)
+			heartbeat = 0;
 	}
 	else if (strcasecmp ("RRARows", key) == 0)
 	{
 		int tmp = atoi (value);
 		if (tmp <= 0)
 		{
