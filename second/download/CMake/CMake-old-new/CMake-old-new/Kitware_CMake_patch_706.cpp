@@ -691,6 +691,9 @@ yyparse(YYPARSE_PARAM_ARG)
     fprintf(stderr, "Starting parse\n");
 #endif
 
+  yylval.Number = 0;
+  yyval.Number = 0;
+   
   yystate = 0;
   yyerrstatus = 0;
   yynerrs = 0;
@@ -712,7 +715,7 @@ yyparse(YYPARSE_PARAM_ARG)
    have just been pushed. so pushing a state here evens the stacks.  */
 yynewstate:
 
-  *++yyssp = yystate;
+  *++yyssp = (short)yystate;
 
   if (yyssp >= yyss + yystacksize - 1)
     {
@@ -1729,6 +1732,7 @@ static int
 yyerror (s)
      char *s ATTRIBUTE_UNUSED;
 {
+  (void)s;
   return 0;
 }
 
@@ -1792,7 +1796,7 @@ LookupWord (yylval, buff)
   /* Make it lowercase. */
   for (p = buff; *p; p++)
     if (ISUPPER ((unsigned char) *p))
-      *p = tolower (*p);
+      *p = (char)tolower (*p);
 
   if (strcmp (buff, "am") == 0 || strcmp (buff, "a.m.") == 0)
     {