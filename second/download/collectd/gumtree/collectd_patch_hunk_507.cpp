 	il->head = item;
 }
 
 #if HAVE_REGEX_H
 static int ignorelist_append_regex(ignorelist_t *il, const char *entry)
 {
-	int rcompile;
-	regex_t *regtemp;
-	int errsize;
-	char *regerr = NULL;
-	ignorelist_item_t *new;
+	regex_t *re;
+	ignorelist_item_t *item;
+	int status;
 
 	/* create buffer */
-	if ((regtemp = malloc(sizeof(regex_t))) == NULL)
+	re = malloc (sizeof (*re));
+	if (re == NULL)
 	{
-		ERROR ("cannot allocate new config entry");
-		return (1);
+		ERROR ("ignorelist_append_regex: malloc failed.");
+		return ENOMEM;
 	}
-	memset (regtemp, '\0', sizeof(regex_t));
+	memset (re, 0, sizeof (*re));
 
 	/* compile regex */
-	if ((rcompile = regcomp (regtemp, entry, REG_EXTENDED)) != 0)
+	status = regcomp (re, entry, REG_EXTENDED);
+	if (status != 0)
 	{
-		/* prepare message buffer */
-		errsize = regerror(rcompile, regtemp, NULL, 0);
-		if (errsize)
-			regerr = smalloc(errsize);
-		/* get error message */
-		if (regerror (rcompile, regtemp, regerr, errsize))
-		{
-			fprintf (stderr, "Cannot compile regex %s: %i/%s",
-					entry, rcompile, regerr);
-			ERROR ("Cannot compile regex %s: %i/%s",
-					entry, rcompile, regerr);
-		}
-		else
-		{
-			fprintf (stderr, "Cannot compile regex %s: %i",
-					entry, rcompile);
-			ERROR ("Cannot compile regex %s: %i",
-					entry, rcompile);
-		}
+		char errbuf[1024];
 
-		if (errsize)
-			sfree (regerr);
-		regfree (regtemp);
-		return (1);
+		(void) regerror (status, re, errbuf, sizeof (errbuf));
+		ERROR ("ignorelist_append_regex: Compiling regular expression \"%s\" failed: %s", entry, errbuf);
+		sfree (re);
+		return status;
 	}
-	DEBUG("regex compiled: %s - %i", entry, rcompile);
 
 	/* create new entry */
-	if ((new = malloc(sizeof(ignorelist_item_t))) == NULL)
+	item = malloc (sizeof (*item));
+	if (item == NULL)
 	{
-		ERROR ("cannot allocate new config entry");
-		regfree (regtemp);
-		return (1);
+		ERROR ("ignorelist_append_regex: malloc failed.");
+		regfree (re);
+		sfree (re);
+		return ENOMEM;
 	}
-	memset (new, '\0', sizeof(ignorelist_item_t));
-	new->rmatch = regtemp;
+	memset (item, 0, sizeof (*item));
+	item->rmatch = re;
 
 	/* append new entry */
-	ignorelist_append (il, new);
+	ignorelist_append (il, item);
 
 	return (0);
 } /* int ignorelist_append_regex(ignorelist_t *il, const char *entry) */
 #endif
 
 static int ignorelist_append_string(ignorelist_t *il, const char *entry)
