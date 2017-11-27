 
 	int values_num;
 	double *values;
 	char **values_names;
 
 	int i;
-	int j;
 
 	fd = socket (PF_UNIX, SOCK_STREAM, 0);
 	if (fd < 0)
 	{
 		fprintf (stderr, "socket failed: %s\n",
 				strerror (errno));
