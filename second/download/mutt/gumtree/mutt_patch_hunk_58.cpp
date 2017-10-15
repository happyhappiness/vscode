   char *includeFile = NULL;
   char *draftFile = NULL;
   char *newMagic = NULL;
   HEADER *msg = NULL;
   LIST *attach = NULL;
   LIST *commands = NULL;
+  LIST *queries = NULL;
+  LIST *alias_queries = NULL;
   int sendflags = 0;
   int flags = 0;
   int version = 0;
   int i;
   int explicit_folder = 0;
+  int dump_variables = 0;
   extern char *optarg;
   extern int optind;
+  int double_dash = argc, nargc = 1;
 
   /* sanity check against stupid administrators */
   
   if(getegid() != getgid())
   {
     fprintf(stderr, "%s: I don't want to run with privileges!\n",
