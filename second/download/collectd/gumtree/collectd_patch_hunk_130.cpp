 		if (fields_num < 1)
 		{
 			fprintf (fhout, "-1 Internal error\n");
 			fclose (fhin);
 			fclose (fhout);
 			pthread_exit ((void *) 1);
-			return ((void *) 1);
 		}
 
 		if (strcasecmp (fields[0], "getval") == 0)
 		{
 			handle_getval (fhout, buffer);
 		}
-		else if (strcasecmp (fields[0], "getthreshold") == 0)
-		{
-			handle_getthreshold (fhout, buffer);
-		}
 		else if (strcasecmp (fields[0], "putval") == 0)
 		{
 			handle_putval (fhout, buffer);
 		}
 		else if (strcasecmp (fields[0], "listval") == 0)
 		{
