 {
     int len = 6;
     const char * fn;
 
     fprintf(fp, POPT_("Usage:"));
     if (!(con->flags & POPT_CONTEXT_KEEP_FIRST)) {
-	/*@-nullderef@*/	/* LCL: wazzup? */
+/*@-boundsread@*/
+	/*@-nullderef -type@*/	/* LCL: wazzup? */
 	fn = con->optionStack->argv[0];
-	/*@=nullderef@*/
+	/*@=nullderef =type@*/
+/*@=boundsread@*/
 	if (fn == NULL) return len;
 	if (strchr(fn, '/')) fn = strrchr(fn, '/') + 1;
 	fprintf(fp, " %s", fn);
 	len += strlen(fn) + 1;
     }
 
     return len;
 }
 
 void poptPrintHelp(poptContext con, FILE * fp, /*@unused@*/ UNUSED(int flags))
 {
-    int leftColWidth;
+    size_t leftColWidth;
 
     (void) showHelpIntro(con, fp);
     if (con->otherHelp)
 	fprintf(fp, " %s\n", con->otherHelp);
     else
 	fprintf(fp, " %s\n", POPT_("[OPTION...]"));
 
     leftColWidth = maxArgWidth(con->options, NULL);
     singleTableHelp(con, fp, con->options, leftColWidth, NULL);
 }
 
 /**
+ * Display usage text for an option.
  * @param fp		output file handle
+ * @param cursor	current display position
  * @param opt		option(s)
  * @param translation_domain	translation domain
  */
-static int singleOptionUsage(FILE * fp, int cursor, 
+static size_t singleOptionUsage(FILE * fp, size_t cursor, 
 		const struct poptOption * opt,
 		/*@null@*/ const char *translation_domain)
 	/*@globals fileSystem @*/
 	/*@modifies *fp, fileSystem @*/
 {
-    int len = 3;
+    size_t len = 4;
     char shortStr[2] = { '\0', '\0' };
     const char * item = shortStr;
     const char * argDescrip = getArgDescrip(opt, translation_domain);
 
-    if (opt->shortName!= '\0' ) {
-	if (!(opt->argInfo & POPT_ARG_MASK)) 
-	    return cursor;	/* we did these already */
+    if (opt->shortName != '\0' && opt->longName != NULL) {
+	len += 2;
+	if (!(opt->argInfo & POPT_ARGFLAG_ONEDASH)) len++;
+	len += strlen(opt->longName);
+    } else if (opt->shortName != '\0') {
 	len++;
 	shortStr[0] = opt->shortName;
 	shortStr[1] = '\0';
     } else if (opt->longName) {
-	len += 1 + strlen(opt->longName);
+	len += strlen(opt->longName);
+	if (!(opt->argInfo & POPT_ARGFLAG_ONEDASH)) len++;
 	item = opt->longName;
     }
 
-    if (len == 3) return cursor;
+    if (len == 4) return cursor;
 
+#ifdef POPT_WCHAR_HACK
+    /* XXX Calculate no. of display characters. */
+    if (argDescrip) {
+	const char * scopy = argDescrip;
+	mbstate_t t;
+	size_t n;
+
+/*@-boundswrite@*/
+	memset ((void *)&t, '\0', sizeof (t));	/* In initial state.  */
+/*@=boundswrite@*/
+	/* Determine number of characters.  */
+	n = mbsrtowcs (NULL, &scopy, strlen(scopy), &t);
+	len += sizeof("=")-1 + n;
+    }
+#else
     if (argDescrip) 
-	len += strlen(argDescrip) + 1;
+	len += sizeof("=")-1 + strlen(argDescrip);
+#endif
 
     if ((cursor + len) > 79) {
 	fprintf(fp, "\n       ");
 	cursor = 7;
     } 
 
-    fprintf(fp, " [-%s%s%s%s]",
-	((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
-	item,
-	(argDescrip ? (opt->shortName != '\0' ? " " : "=") : ""),
-	(argDescrip ? argDescrip : ""));
+    if (opt->longName && opt->shortName) {
+	fprintf(fp, " [-%c|-%s%s%s%s]",
+	    opt->shortName, ((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "" : "-"),
+	    opt->longName,
+	    (argDescrip ? " " : ""),
+	    (argDescrip ? argDescrip : ""));
+    } else {
+	fprintf(fp, " [-%s%s%s%s]",
+	    ((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
+	    item,
+	    (argDescrip ? (opt->shortName != '\0' ? " " : "=") : ""),
+	    (argDescrip ? argDescrip : ""));
+    }
 
     return cursor + len + 1;
 }
 
 /**
  * Display popt alias and exec usage.
  * @param fp		output file handle
+ * @param cursor	current display position
  * @param item		alias/exec array
  * @param nitems	no. of ara/exec entries
  * @param translation_domain	translation domain
  */
-static int itemUsage(FILE * fp, int cursor, poptItem item, int nitems,
-		/*@null@*/ const char * translation_domain)
+static size_t itemUsage(FILE * fp, size_t cursor,
+		/*@null@*/ poptItem item, int nitems,
+		/*@null@*/ UNUSED(const char * translation_domain))
 	/*@globals fileSystem @*/
 	/*@modifies *fp, fileSystem @*/
 {
     int i;
 
     /*@-branchstate@*/		/* FIX: W2DO? */
