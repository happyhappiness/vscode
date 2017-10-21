 		*s++='\0';
 	else
 		more=0;
 	return(t);
 }
 
-	
-void add_exclude_line(char *p)
-{
-	char *tok;
-	if (!p || !*p) return;
-	p = strdup(p);
-	if (!p) out_of_memory("add_exclude_line");
- 	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
-		add_exclude(tok, 0);
-	free(p);
-}
 
-void add_include_line(char *p)
+void add_exclude_line(struct exclude_struct ***listp,
+		      const char *line, int include)
 {
-	char *tok;
-	if (!p || !*p) return;
-	p = strdup(p);
-	if (!p) out_of_memory("add_include_line");
+	char *tok, *p;
+	if (!line || !*line) return;
+	p = strdup(line);
+	if (!p) out_of_memory("add_exclude_line");
 	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
-		add_exclude(tok, 1);
+		add_exclude(listp, tok, include);
 	free(p);
 }
 
 
 static char *cvs_ignore_list[] = {
   "RCS/", "SCCS/", "CVS/", ".svn/", "CVS.adm", "RCSLOG", "cvslog.*",
