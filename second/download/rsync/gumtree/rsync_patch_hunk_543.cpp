 		if (l >= MAXPATHLEN) overflow("recv_exclude_list");
 		read_sbuf(f,line,l);
 		add_exclude(line,0);
 	}
 }
 
+/* Get the next include/exclude arg from the string. It works in a similar way
+** to strtok - initially an arg is sent over, from then on NULL. This
+** routine takes into account any +/- in the strings and does not
+** consider the space following it as a delimeter.
+*/
+char *get_exclude_tok(char *p)
+{
+	static char *s;
+	static int more;
+	char *t;
+
+	if (p) {
+		s=p;
+		if (*p)
+			more=1;
+	}
+
+	if (!more)
+		return(NULL);
+
+	/* Skip over any initial spaces */
+	while(isspace(*s))
+		s++;
+
+	/* Are we at the end of the string? */
+	if (*s) {
+		/* remember the beginning of the token */
+		t=s;
+
+		/* Is this a '+' or '-' followed by a space (not whitespace)? */
+		if ((*s=='+' || *s=='-') && *(s+1)==' ')
+			s+=2;
+	
+		/* Skip to the next space or the end of the string */
+		while(!isspace(*s) && *s!='\0')
+			s++;
+	} else {
+		t=NULL;
+	}
 
+	/* Have we reached the end of the string? */
+	if (*s)
+		*s++='\0';
+	else
+		more=0;
+	return(t);
+}
+
+	
 void add_exclude_line(char *p)
 {
 	char *tok;
 	if (!p || !*p) return;
 	p = strdup(p);
 	if (!p) out_of_memory("add_exclude_line");
-	for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
+ 	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
 		add_exclude(tok, 0);
 	free(p);
 }
 
 void add_include_line(char *p)
 {
 	char *tok;
 	if (!p || !*p) return;
 	p = strdup(p);
 	if (!p) out_of_memory("add_include_line");
-	for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
+	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
 		add_exclude(tok, 1);
 	free(p);
 }
 
 
 static char *cvs_ignore_list[] = {
