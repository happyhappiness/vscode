 	return 0;
 
     fprintf(fp, " [-%s]", s);
     return strlen(s) + 4;
 }
 
-void poptPrintUsage(poptContext con, FILE * fp, /*@unused@*/ int flags)
+void poptPrintUsage(poptContext con, FILE * fp, /*@unused@*/ UNUSED(int flags))
 {
     int cursor;
 
     cursor = showHelpIntro(con, fp);
     cursor += showShortOptions(con->options, fp, NULL);
     (void) singleTableUsage(con, fp, cursor, con->options, NULL);
