 	lcc_identifier_t *ret_ident = NULL;
 	size_t ret_ident_num = 0;
 
 	char *hostname = NULL;
 
 	int status;
-	size_t i;
 
 	status = lcc_listval (connection, &ret_ident, &ret_ident_num);
 	if (status != 0) {
 		printf ("UNKNOWN: %s\n", lcc_strerror (connection));
 		if (ret_ident != NULL)
 			free (ret_ident);
