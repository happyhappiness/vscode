 	il->head = item;
 }
 
 #if HAVE_REGEX_H
 static int ignorelist_append_regex(ignorelist_t *il, const char *entry)
 {
-	regex_t *re;
-	ignorelist_item_t *item;
-	int status;
+	int rcompile;
+	regex_t *regtemp;
+	int errsize;
+	char *regerr = NULL;
+	ignorelist_item_t *new;
 
 	/* create buffer */
-	re = malloc (sizeof (*re));
-	if (re == NULL)
+	if ((regtemp = malloc(sizeof(regex_t))) == NULL)
 	{
-		ERROR ("ignorelist_append_regex: malloc failed.");
-		return ENOMEM;
+		ERROR ("cannot allocate new config entry");
+		return (1);
 	}
-	memset (re, 0, sizeof (*re));
+	memset (regtemp, '\0', sizeof(regex_t));
 
 	/* compile regex */
-	status = regcomp (re, entry, REG_EXTENDED);
-	if (status != 0)
+	if ((rcompile = regcomp (regtemp, entry, REG_EXTENDED)) != 0)
 	{
-		char errbuf[1024];
+		/* prepare message buffer */
+		errsize = regerror(rcompile, regtemp, NULL, 0);
+		if (errsize)
+			regerr = smalloc(errsize);
+		/* get error message */
+		if (regerror (rcompile, regtemp, regerr, errsize))
+		{
+			fprintf (stderr, "Cannot compile regex %s: %i/%s",
+					entry, rcompile, regerr);
+			ERROR ("Cannot compile regex %s: %i/%s",
+					entry, rcompile, regerr);
+		}
+		else
+		{
+			fprintf (stderr, "Cannot compile regex %s: %i",
+					entry, rcompile);
+			ERROR ("Cannot compile regex %s: %i",
+					entry, rcompile);
+		}
 
-		(void) regerror (status, re, errbuf, sizeof (errbuf));
-		ERROR ("ignorelist_append_regex: Compiling regular expression \"%s\" failed: %s", entry, errbuf);
-		sfree (re);
-		return status;
+		if (errsize)
+			sfree (regerr);
+		regfree (regtemp);
+		return (1);
 	}
+	DEBUG("regex compiled: %s - %i", entry, rcompile);
 
 	/* create new entry */
-	item = malloc (sizeof (*item));
-	if (item == NULL)
+	if ((new = malloc(sizeof(ignorelist_item_t))) == NULL)
 	{
-		ERROR ("ignorelist_append_regex: malloc failed.");
-		regfree (re);
-		sfree (re);
-		return ENOMEM;
+		ERROR ("cannot allocate new config entry");
+		regfree (regtemp);
+		return (1);
 	}
-	memset (item, 0, sizeof (*item));
-	item->rmatch = re;
+	memset (new, '\0', sizeof(ignorelist_item_t));
+	new->rmatch = regtemp;
 
 	/* append new entry */
-	ignorelist_append (il, item);
+	ignorelist_append (il, new);
 
 	return (0);
 } /* int ignorelist_append_regex(ignorelist_t *il, const char *entry) */
 #endif
 
 static int ignorelist_append_string(ignorelist_t *il, const char *entry)
