 #endif
   /* Make sure YYID is used.  */
   return YYID (yyresult);
 }
 
 
-#line 190 "parser.y"
+#line 192 "parser.y"
 
 static int yyerror (const char *s)
 {
-	char *text;
-
-	if (*yytext == '\n')
-		text = "<newline>";
-	else
-		text = yytext;
-
-	fprintf (stderr, "Parse error in file `%s', line %i near `%s': %s\n",
-		c_file, yylineno, text, s);
+	fprintf (stderr, "Error in line %i near `%s': %s\n", yylineno, yytext, s);
 	return (-1);
 } /* int yyerror */
 
 static char *unquote (const char *orig)
 {
 	char *ret = strdup (orig);
