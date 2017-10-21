 		    return POPT_ERROR_BADOPT;
 	    }
 
 	    if (!opt) {
 		con->os->nextCharArg = origOptString + 1;
 	    } else {
-		if(con->os == con->optionStack &&
-		   opt->argInfo & POPT_ARGFLAG_STRIP) {
+		if (con->os == con->optionStack &&
+		   opt->argInfo & POPT_ARGFLAG_STRIP)
+		{
 		    canstrip = 1;
 		    poptStripArg(con, thisopt);
 		}
+		shorty = 0;
 	    }
 	}
 
 	/* Process next short option */
+	/*@-branchstate@*/		/* FIX: W2DO? */
 	if (con->os->nextCharArg) {
 	    origOptString = con->os->nextCharArg;
 
 	    con->os->nextCharArg = NULL;
 
-	    if (handleAlias(con, NULL, *origOptString,
-			    origOptString + 1)) {
+	    if (handleAlias(con, NULL, *origOptString, origOptString + 1))
+		continue;
+
+	    if (handleExec(con, NULL, *origOptString)) {
+		/* Restore rest of short options for further processing */
 		origOptString++;
+		if (*origOptString != '\0')
+		    con->os->nextCharArg = origOptString;
 		continue;
 	    }
-	    if (handleExec(con, NULL, *origOptString))
-		continue;
 
 	    opt = findOption(con->options, NULL, *origOptString, &cb,
 			     &cbData, 0);
 	    if (!opt)
 		return POPT_ERROR_BADOPT;
+	    shorty = 1;
 
 	    origOptString++;
-	    if (*origOptString)
+	    if (*origOptString != '\0')
 		con->os->nextCharArg = origOptString;
 	}
+	/*@=branchstate@*/
 
+	if (opt == NULL) return POPT_ERROR_BADOPT;	/* XXX can't happen */
 	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE) {
-	    *((int *)opt->arg) = 1;
+	    if (poptSaveInt(opt, 1L))
+		return POPT_ERROR_BADOPERATION;
 	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL) {
-	    if (opt->arg)
-		*((int *) opt->arg) = opt->val;
-	} else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
-	    if (con->os->nextArg) {
-		xfree(con->os->nextArg);
-		con->os->nextArg = NULL;
+	    if (opt->arg) {
+		if (poptSaveInt(opt, (long)opt->val))
+		    return POPT_ERROR_BADOPERATION;
 	    }
+	} else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
+	    con->os->nextArg = _free(con->os->nextArg);
+	    /*@-usedef@*/	/* FIX: W2DO? */
 	    if (longArg) {
-		con->os->nextArg = expandNextArg(con, longArg);
+	    /*@=usedef@*/
+		longArg = expandNextArg(con, longArg);
+		con->os->nextArg = longArg;
 	    } else if (con->os->nextCharArg) {
-		con->os->nextArg = expandNextArg(con, con->os->nextCharArg);
+		longArg = expandNextArg(con, con->os->nextCharArg);
+		con->os->nextArg = longArg;
 		con->os->nextCharArg = NULL;
 	    } else {
 		while (con->os->next == con->os->argc &&
 		       con->os > con->optionStack) {
 		    cleanOSE(con->os--);
 		}
-		if (con->os->next == con->os->argc)
-		    return POPT_ERROR_NOARG;
-
-		/* make sure this isn't part of a short arg or the
-                   result of an alias expansion */
-		if(con->os == con->optionStack &&
-		   opt->argInfo & POPT_ARGFLAG_STRIP &&
-		   canstrip) {
-		    poptStripArg(con, con->os->next);
-		}
+		if (con->os->next == con->os->argc) {
+		    if (!(opt->argInfo & POPT_ARGFLAG_OPTIONAL))
+			/*@-compdef@*/	/* FIX: con->os->argv not defined */
+			return POPT_ERROR_NOARG;
+			/*@=compdef@*/
+		    con->os->nextArg = NULL;
+		} else {
+
+		    /*
+		     * Make sure this isn't part of a short arg or the
+		     * result of an alias expansion.
+		     */
+		    if (con->os == con->optionStack &&
+			(opt->argInfo & POPT_ARGFLAG_STRIP) &&
+			canstrip) {
+			poptStripArg(con, con->os->next);
+		    }
 		
-		con->os->nextArg = expandNextArg(con, con->os->argv[con->os->next++]);
+		    if (con->os->argv != NULL) {	/* XXX can't happen */
+			/* XXX watchout: subtle side-effects live here. */
+			longArg = con->os->argv[con->os->next++];
+			longArg = expandNextArg(con, longArg);
+			con->os->nextArg = longArg;
+		    }
+		}
 	    }
+	    longArg = NULL;
 
 	    if (opt->arg) {
-		long aLong;
-		char *end;
-
 		switch (opt->argInfo & POPT_ARG_MASK) {
-		  case POPT_ARG_STRING:
+		case POPT_ARG_STRING:
 		    /* XXX memory leak, hard to plug */
-		    *((const char **) opt->arg) = xstrdup(con->os->nextArg);
-		    break;
-
-		  case POPT_ARG_INT:
-		  case POPT_ARG_LONG:
-		    aLong = strtol(con->os->nextArg, &end, 0);
-		    if (!(end && *end == '\0'))
-			return POPT_ERROR_BADNUMBER;
+		    *((const char **) opt->arg) = (con->os->nextArg)
+			? xstrdup(con->os->nextArg) : NULL;
+		    /*@switchbreak@*/ break;
+
+		case POPT_ARG_INT:
+		case POPT_ARG_LONG:
+		{   long aLong = 0;
+		    char *end;
+
+		    if (con->os->nextArg) {
+			aLong = strtol(con->os->nextArg, &end, 0);
+			if (!(end && *end == '\0'))
+			    return POPT_ERROR_BADNUMBER;
+		    }
 
-		    if (aLong == LONG_MIN || aLong == LONG_MAX)
-			return POPT_ERROR_OVERFLOW;
 		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_LONG) {
-			*((long *) opt->arg) = aLong;
+			if (aLong == LONG_MIN || aLong == LONG_MAX)
+			    return POPT_ERROR_OVERFLOW;
+			if (poptSaveLong(opt, aLong))
+			    return POPT_ERROR_BADOPERATION;
 		    } else {
 			if (aLong > INT_MAX || aLong < INT_MIN)
 			    return POPT_ERROR_OVERFLOW;
-			*((int *) opt->arg) = aLong;
+			if (poptSaveInt(opt, aLong))
+			    return POPT_ERROR_BADOPERATION;
 		    }
-		    break;
+		}   /*@switchbreak@*/ break;
 
-		  default:
-		    fprintf(stdout, POPT_("option type (%d) not implemented in popt\n"),
-		      opt->argInfo & POPT_ARG_MASK);
+		case POPT_ARG_FLOAT:
+		case POPT_ARG_DOUBLE:
+		{   double aDouble = 0.0;
+		    char *end;
+
+		    if (con->os->nextArg) {
+			/*@-mods@*/
+			int saveerrno = errno;
+			errno = 0;
+			aDouble = strtod(con->os->nextArg, &end);
+			if (errno == ERANGE)
+			    return POPT_ERROR_OVERFLOW;
+			errno = saveerrno;
+			/*@=mods@*/
+			if (*end != '\0')
+			    return POPT_ERROR_BADNUMBER;
+		    }
+
+		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_DOUBLE) {
+			*((double *) opt->arg) = aDouble;
+		    } else {
+#ifndef DBL_EPSILON
+#define DBL_EPSILON 2.2204460492503131e-16
+#endif
+#define _ABS(a)	((((a) - 0.0) < DBL_EPSILON) ? -(a) : (a))
+			if ((_ABS(aDouble) - FLT_MAX) > DBL_EPSILON)
+			    return POPT_ERROR_OVERFLOW;
+			if ((FLT_MIN - _ABS(aDouble)) > DBL_EPSILON)
+			    return POPT_ERROR_OVERFLOW;
+			*((float *) opt->arg) = aDouble;
+		    }
+		}   /*@switchbreak@*/ break;
+		default:
+		    fprintf(stdout,
+			POPT_("option type (%d) not implemented in popt\n"),
+			(opt->argInfo & POPT_ARG_MASK));
 		    exit(EXIT_FAILURE);
+		    /*@notreached@*/ /*@switchbreak@*/ break;
 		}
 	    }
 	}
 
-	if (cb)
-	    cb(con, POPT_CALLBACK_REASON_OPTION, opt, con->os->nextArg, cbData);
-	else if (opt->val && ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL))
+	if (cb) {
+	    /*@-internalglobs@*/
+	    invokeCallbacksOPTION(con, con->options, opt, cbData, shorty);
+	    /*@=internalglobs@*/
+	} else if (opt->val && ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL))
 	    done = 1;
 
 	if ((con->finalArgvCount + 2) >= (con->finalArgvAlloced)) {
 	    con->finalArgvAlloced += 10;
 	    con->finalArgv = realloc(con->finalArgv,
 			    sizeof(*con->finalArgv) * con->finalArgvAlloced);
 	}
 
-	{    char *s = malloc((opt->longName ? strlen(opt->longName) : 0) + 3);
-	    if (opt->longName)
-		sprintf(s, "--%s", opt->longName);
-	    else
-		sprintf(s, "-%c", opt->shortName);
-	    con->finalArgv[con->finalArgvCount++] = s;
+	if (con->finalArgv != NULL)
+	{   char *s = malloc((opt->longName ? strlen(opt->longName) : 0) + 3);
+	    if (s != NULL) {	/* XXX can't happen */
+		if (opt->longName)
+		    sprintf(s, "%s%s",
+			((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "-" : "--"),
+			opt->longName);
+		else
+		    sprintf(s, "-%c", opt->shortName);
+		con->finalArgv[con->finalArgvCount++] = s;
+	    } else
+		con->finalArgv[con->finalArgvCount++] = NULL;
 	}
 
-	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE
-		     && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL) {
-	    con->finalArgv[con->finalArgvCount++] = xstrdup(con->os->nextArg);
+	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE)
+	    /*@-ifempty@*/ ; /*@=ifempty@*/
+	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL)
+	    /*@-ifempty@*/ ; /*@=ifempty@*/
+	else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
+	    if (con->finalArgv != NULL && con->os->nextArg)
+	        con->finalArgv[con->finalArgvCount++] =
+			/*@-nullpass@*/	/* LCL: con->os->nextArg != NULL */
+			xstrdup(con->os->nextArg);
+			/*@=nullpass@*/
 	}
     }
 
-    return opt->val;
+    return (opt ? opt->val : -1);	/* XXX can't happen */
 }
 
-const char * poptGetOptArg(poptContext con) {
-    const char * ret = con->os->nextArg;
-    con->os->nextArg = NULL;
+const char * poptGetOptArg(poptContext con)
+{
+    const char * ret = NULL;
+    /*@-branchstate@*/
+    if (con) {
+	ret = con->os->nextArg;
+	con->os->nextArg = NULL;
+    }
+    /*@=branchstate@*/
     return ret;
 }
 
-const char * poptGetArg(poptContext con) {
-    if (con->numLeftovers == con->nextLeftover) return NULL;
-    return con->leftovers[con->nextLeftover++];
+const char * poptGetArg(poptContext con)
+{
+    const char * ret = NULL;
+    if (con && con->leftovers != NULL && con->nextLeftover < con->numLeftovers)
+	ret = con->leftovers[con->nextLeftover++];
+    return ret;
 }
 
-const char * poptPeekArg(poptContext con) {
-    if (con->numLeftovers == con->nextLeftover) return NULL;
-    return con->leftovers[con->nextLeftover];
+const char * poptPeekArg(poptContext con)
+{
+    const char * ret = NULL;
+    if (con && con->leftovers != NULL && con->nextLeftover < con->numLeftovers)
+	ret = con->leftovers[con->nextLeftover];
+    return ret;
 }
 
-const char ** poptGetArgs(poptContext con) {
-    if (con->numLeftovers == con->nextLeftover) return NULL;
+const char ** poptGetArgs(poptContext con)
+{
+    if (con == NULL ||
+	con->leftovers == NULL || con->numLeftovers == con->nextLeftover)
+	return NULL;
 
     /* some apps like [like RPM ;-) ] need this NULL terminated */
     con->leftovers[con->numLeftovers] = NULL;
 
+    /*@-nullret -nullstate @*/	/* FIX: typedef double indirection. */
     return (con->leftovers + con->nextLeftover);
+    /*@=nullret =nullstate @*/
 }
 
-void poptFreeContext(poptContext con) {
+poptContext poptFreeContext(poptContext con)
+{
+    poptItem item;
     int i;
 
+    if (con == NULL) return con;
     poptResetContext(con);
-    if (con->os->argb) free(con->os->argb);
+    con->os->argb = _free(con->os->argb);
 
+    if (con->aliases != NULL)
     for (i = 0; i < con->numAliases; i++) {
-	if (con->aliases[i].longName) xfree(con->aliases[i].longName);
-	free(con->aliases[i].argv);
+	item = con->aliases + i;
+	/*@-modobserver -observertrans -dependenttrans@*/
+	item->option.longName = _free(item->option.longName);
+	item->option.descrip = _free(item->option.descrip);
+	item->option.argDescrip = _free(item->option.argDescrip);
+	/*@=modobserver =observertrans =dependenttrans@*/
+	item->argv = _free(item->argv);
     }
+    con->aliases = _free(con->aliases);
 
+    if (con->execs != NULL)
     for (i = 0; i < con->numExecs; i++) {
-	if (con->execs[i].longName) xfree(con->execs[i].longName);
-	xfree(con->execs[i].script);
-    }
-    if (con->execs) xfree(con->execs);
-
-    free(con->leftovers);
-    free(con->finalArgv);
-    if (con->appName) xfree(con->appName);
-    if (con->aliases) free(con->aliases);
-    if (con->otherHelp) xfree(con->otherHelp);
-    if (con->execPath) xfree(con->execPath);
-    if (con->arg_strip) PBM_FREE(con->arg_strip);
+	item = con->execs + i;
+	/*@-modobserver -observertrans -dependenttrans@*/
+	item->option.longName = _free(item->option.longName);
+	item->option.descrip = _free(item->option.descrip);
+	item->option.argDescrip = _free(item->option.argDescrip);
+	/*@=modobserver =observertrans =dependenttrans@*/
+	item->argv = _free(item->argv);
+    }
+    con->execs = _free(con->execs);
+
+    con->leftovers = _free(con->leftovers);
+    con->finalArgv = _free(con->finalArgv);
+    con->appName = _free(con->appName);
+    con->otherHelp = _free(con->otherHelp);
+    con->execPath = _free(con->execPath);
+    con->arg_strip = PBM_FREE(con->arg_strip);
     
-    free(con);
+    con = _free(con);
+    return con;
 }
 
-int poptAddAlias(poptContext con, struct poptAlias newAlias,
+int poptAddAlias(poptContext con, struct poptAlias alias,
 		/*@unused@*/ int flags)
 {
-    int aliasNum = con->numAliases++;
-    struct poptAlias * alias;
+    poptItem item = (poptItem) alloca(sizeof(*item));
+    memset(item, 0, sizeof(*item));
+    item->option.longName = alias.longName;
+    item->option.shortName = alias.shortName;
+    item->option.argInfo = POPT_ARGFLAG_DOC_HIDDEN;
+    item->option.arg = 0;
+    item->option.val = 0;
+    item->option.descrip = NULL;
+    item->option.argDescrip = NULL;
+    item->argc = alias.argc;
+    item->argv = alias.argv;
+    return poptAddItem(con, item, 0);
+}
 
-    /* SunOS won't realloc(NULL, ...) */
-    if (!con->aliases)
-	con->aliases = malloc(sizeof(newAlias) * con->numAliases);
-    else
-	con->aliases = realloc(con->aliases,
-			       sizeof(newAlias) * con->numAliases);
-    alias = con->aliases + aliasNum;
-
-    alias->longName = (newAlias.longName)
-	? strcpy(malloc(strlen(newAlias.longName) + 1), newAlias.longName)
-	: NULL;
-    alias->shortName = newAlias.shortName;
-    alias->argc = newAlias.argc;
-    alias->argv = newAlias.argv;
+/*@-mustmod@*/ /* LCL: con not modified? */
+int poptAddItem(poptContext con, poptItem newItem, int flags)
+{
+    poptItem * items, item;
+    int * nitems;
+
+    switch (flags) {
+    case 1:
+	items = &con->execs;
+	nitems = &con->numExecs;
+	break;
+    case 0:
+	items = &con->aliases;
+	nitems = &con->numAliases;
+	break;
+    default:
+	return 1;
+	/*@notreached@*/ break;
+    }
+
+    *items = realloc((*items), ((*nitems) + 1) * sizeof(**items));
+    if ((*items) == NULL)
+	return 1;
+
+    item = (*items) + (*nitems);
+
+    item->option.longName =
+	(newItem->option.longName ? xstrdup(newItem->option.longName) : NULL);
+    item->option.shortName = newItem->option.shortName;
+    item->option.argInfo = newItem->option.argInfo;
+    item->option.arg = newItem->option.arg;
+    item->option.val = newItem->option.val;
+    item->option.descrip =
+	(newItem->option.descrip ? xstrdup(newItem->option.descrip) : NULL);
+    item->option.argDescrip =
+       (newItem->option.argDescrip ? xstrdup(newItem->option.argDescrip) : NULL);
+    item->argc = newItem->argc;
+    item->argv = newItem->argv;
+
+    (*nitems)++;
 
     return 0;
 }
+/*@=mustmod@*/
 
-const char * poptBadOption(poptContext con, int flags) {
-    struct optionStackEntry * os;
+const char * poptBadOption(poptContext con, int flags)
+{
+    struct optionStackEntry * os = NULL;
 
-    if (flags & POPT_BADOPTION_NOALIAS)
-	os = con->optionStack;
-    else
-	os = con->os;
+    if (con != NULL)
+	os = (flags & POPT_BADOPTION_NOALIAS) ? con->optionStack : con->os;
 
-    return os->argv[os->next - 1];
+    /*@-nullderef@*/	/* LCL: os->argv != NULL */
+    return (os && os->argv ? os->argv[os->next - 1] : NULL);
+    /*@=nullderef@*/
 }
 
-#define POPT_ERROR_NOARG	-10
-#define POPT_ERROR_BADOPT	-11
-#define POPT_ERROR_OPTSTOODEEP	-13
-#define POPT_ERROR_BADQUOTE	-15	/* only from poptParseArgString() */
-#define POPT_ERROR_ERRNO	-16	/* only from poptParseArgString() */
-
-const char *const poptStrerror(const int error) {
+const char *const poptStrerror(const int error)
+{
     switch (error) {
       case POPT_ERROR_NOARG:
 	return POPT_("missing argument");
       case POPT_ERROR_BADOPT:
 	return POPT_("unknown option");
+      case POPT_ERROR_BADOPERATION:
+	return POPT_("mutually exclusive logical operations requested");
+      case POPT_ERROR_NULLARG:
+	return POPT_("opt->arg should not be NULL");
       case POPT_ERROR_OPTSTOODEEP:
 	return POPT_("aliases nested too deeply");
       case POPT_ERROR_BADQUOTE:
-	return POPT_("error in paramter quoting");
+	return POPT_("error in parameter quoting");
       case POPT_ERROR_BADNUMBER:
 	return POPT_("invalid numeric value");
       case POPT_ERROR_OVERFLOW:
 	return POPT_("number too large or too small");
+      case POPT_ERROR_MALLOC:
+	return POPT_("memory allocation failed");
       case POPT_ERROR_ERRNO:
 	return strerror(errno);
       default:
 	return POPT_("unknown error");
     }
 }
 
-int poptStuffArgs(poptContext con, const char ** argv) {
+int poptStuffArgs(poptContext con, const char ** argv)
+{
     int argc;
+    int rc;
 
     if ((con->os - con->optionStack) == POPT_OPTION_DEPTH)
 	return POPT_ERROR_OPTSTOODEEP;
 
     for (argc = 0; argv[argc]; argc++)
-	;
+	{};
 
     con->os++;
     con->os->next = 0;
     con->os->nextArg = NULL;
     con->os->nextCharArg = NULL;
     con->os->currAlias = NULL;
-    poptDupArgv(argc, argv, &con->os->argc, &con->os->argv);
+    rc = poptDupArgv(argc, argv, &con->os->argc, &con->os->argv);
     con->os->argb = NULL;
     con->os->stuffed = 1;
 
-    return 0;
+    return rc;
 }
 
-const char * poptGetInvocationName(poptContext con) {
-    return con->os->argv[0];
+const char * poptGetInvocationName(poptContext con)
+{
+    return (con->os->argv ? con->os->argv[0] : "");
 }
 
-int poptStrippedArgv(poptContext con, int argc, char **argv)
+int poptStrippedArgv(poptContext con, int argc, char ** argv)
 {
-    int i,j=1, numargs=argc;
+    int numargs = argc;
+    int j = 1;
+    int i;
     
-    for(i=1; i<argc; i++) {
-	if(PBM_ISSET(i, con->arg_strip)) {
+    /*@-sizeoftype@*/
+    if (con->arg_strip)
+    for (i = 1; i < argc; i++) {
+	if (PBM_ISSET(i, con->arg_strip))
 	    numargs--;
-	}
     }
     
-    for(i=1; i<argc; i++) {
-	if(PBM_ISSET(i, con->arg_strip)) {
+    for (i = 1; i < argc; i++) {
+	if (con->arg_strip && PBM_ISSET(i, con->arg_strip))
 	    continue;
-	} else {
-	    if(j<numargs) {
-		argv[j++]=argv[i];
-	    } else {
-		argv[j++]='\0';
-	    }
-	}
+	argv[j] = (j < numargs) ? argv[i] : NULL;
+	j++;
     }
+    /*@=sizeoftype@*/
     
-    return(numargs);
+    return numargs;
 }
