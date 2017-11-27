 
 /* Copy whatever the last rule matched to the standard output. */
 #ifndef ECHO
 /* This used to be an fputs(), but since the string might contain NUL's,
  * we now use fwrite().
  */
-#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
+#define ECHO fwrite( yytext, yyleng, 1, yyout )
 #endif
 
 /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
  * is returned in "result".
  */
 #ifndef YY_INPUT
