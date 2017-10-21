 	  read_sbuf(f,line,l);
 	  add_exclude(line);
   }
 }
 
 
+void add_exclude_line(char *p)
+{
+	char *tok;
+	if (!p || !*p) return;
+	p = strdup(p);
+	if (!p) out_of_memory("add_exclude_line");
+	for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
+		add_exclude(tok);
+	free(p);
+}
+
+
 static char *cvs_ignore_list[] = {
   "RCS","SCCS","CVS","CVS.adm","RCSLOG","cvslog.*",
   "tags","TAGS",".make.state",".nse_depinfo",
   "*~", "#*", ".#*", ",*", "*.old", "*.bak", "*.BAK", "*.orig",
   "*.rej", ".del-*", "*.a", "*.o", "*.obj", "*.so", "*.Z", "*.elc", "*.ln",
   "core",NULL};
