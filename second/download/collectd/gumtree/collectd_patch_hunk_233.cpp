 	{
 		double tmp = atof (value);
 		if ((tmp < 0.0) || (tmp >= 1.0))
 		{
 			fprintf (stderr, "rrdtool: `XFF' must "
 					"be in the range 0 to 1 (exclusive).");
+			ERROR ("rrdtool: `XFF' must "
+					"be in the range 0 to 1 (exclusive).");
 			return (1);
 		}
 		xff = tmp;
 	}
 	else
 	{
