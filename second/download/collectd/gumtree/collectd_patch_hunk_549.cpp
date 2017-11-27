 static int listval (lcc_connection_t *c, int argc, char **argv)
 {
   lcc_identifier_t *ret_ident     = NULL;
   size_t            ret_ident_num = 0;
 
   int status;
-  size_t i;
 
   assert (strcasecmp (argv[0], "listval") == 0);
 
   if (argc != 1) {
     fprintf (stderr, "ERROR: listval: Does not accept any arguments.\n");
     return (-1);
