 				datadir = NULL;
 			}
 		}
 	}
 	else if (strcasecmp ("StepSize", key) == 0)
 	{
-		stepsize = atoi (value);
-		if (stepsize < 0)
-			stepsize = 0;
+		int temp = atoi (value);
+		if (temp > 0)
+			rrdcreate_config.stepsize = temp;
 	}
 	else if (strcasecmp ("HeartBeat", key) == 0)
 	{
-		heartbeat = atoi (value);
-		if (heartbeat < 0)
-			heartbeat = 0;
+		int temp = atoi (value);
+		if (temp > 0)
+			rrdcreate_config.heartbeat = temp;
 	}
 	else if (strcasecmp ("RRARows", key) == 0)
 	{
 		int tmp = atoi (value);
 		if (tmp <= 0)
 		{
 			fprintf (stderr, "rrdtool: `RRARows' must "
 					"be greater than 0.\n");
 			ERROR ("rrdtool: `RRARows' must "
 					"be greater than 0.\n");
 			return (1);
 		}
-		rrarows = tmp;
+		rrdcreate_config.rrarows = tmp;
 	}
 	else if (strcasecmp ("RRATimespan", key) == 0)
 	{
 		char *saveptr = NULL;
 		char *dummy;
 		char *ptr;
