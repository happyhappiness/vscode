 FN_LOCAL_INTEGER(lp_max_connections, max_connections)
 FN_LOCAL_INTEGER(lp_max_verbosity, max_verbosity)
 FN_LOCAL_INTEGER(lp_syslog_facility, syslog_facility)
 FN_LOCAL_INTEGER(lp_timeout, timeout)
 
 FN_LOCAL_BOOL(lp_fake_super, fake_super)
+FN_LOCAL_BOOL(lp_forward_lookup, forward_lookup)
 FN_LOCAL_BOOL(lp_ignore_errors, ignore_errors)
 FN_LOCAL_BOOL(lp_ignore_nonreadable, ignore_nonreadable)
 FN_LOCAL_BOOL(lp_list, list)
 FN_LOCAL_BOOL(lp_munge_symlinks, munge_symlinks)
 FN_LOCAL_BOOL(lp_numeric_ids, numeric_ids)
 FN_LOCAL_BOOL(lp_read_only, read_only)
+FN_LOCAL_BOOL(lp_reverse_lookup, reverse_lookup)
 FN_LOCAL_BOOL(lp_strict_modes, strict_modes)
 FN_LOCAL_BOOL(lp_transfer_logging, transfer_logging)
 FN_LOCAL_BOOL(lp_use_chroot, use_chroot)
 FN_LOCAL_BOOL(lp_write_only, write_only)
 
-/* local prototypes */
-static int    strwicmp(char *psz1, char *psz2);
-static int    map_parameter(char *parmname);
-static BOOL   set_boolean(BOOL *pb, char *parmvalue);
-static int    getservicebyname(char *name, service *pserviceDest);
-static void   copy_service(service *pserviceDest, service *pserviceSource);
-static BOOL   do_parameter(char *parmname, char *parmvalue);
-static BOOL   do_section(char *sectionname);
-
-
-/***************************************************************************
-* initialise a service to the defaults
-***************************************************************************/
-static void init_service(service *pservice)
-{
-	memset((char *)pservice,0,sizeof(service));
-	copy_service(pservice,&sDefault);
-}
-
-
-/**
- * Assign a copy of @p v to @p *s.  Handles NULL strings.  @p *v must
- * be initialized when this is called, either to NULL or a malloc'd
- * string.
- *
- * @fixme There is a small leak here in that sometimes the existing
- * value will be dynamically allocated, and the old copy is lost.
- * However, we can't always deallocate the old value, because in the
- * case of sDefault, it points to a static string.  It would be nice
- * to have either all-strdup'd values, or to never need to free
- * memory.
- **/
-static void string_set(char **s, const char *v)
+/* Assign a copy of v to *s.  Handles NULL strings.  We don't worry
+ * about overwriting a malloc'd string because the long-running
+ * (port-listening) daemon only loads the config file once, and the
+ * per-job (forked or xinitd-ran) daemon only re-reads the file at
+ * the start, so any lost memory is inconsequential. */
+static inline void string_set(char **s, const char *v)
 {
-	if (!v) {
+	if (!v)
 		*s = NULL;
-		return;
-	}
-	*s = strdup(v);
-	if (!*s)
-		exit_cleanup(RERR_MALLOC);
+	else if (!(*s = strdup(v)))
+		out_of_memory("string_set");
 }
 
+/* Copy the local_vars, strdup'ing any strings.  NOTE:  this depends on
+ * the structure starting with a contiguous list of the char* variables,
+ * and having an accurate count in the LOCAL_STRING_COUNT() macro. */
+static void copy_section(local_vars *psectionDest, local_vars *psectionSource)
+{
+	int count = LOCAL_STRING_COUNT();
+	char **strings = (char**)psectionDest;
+
+	memcpy(psectionDest, psectionSource, sizeof psectionDest[0]);
+	while (count--) {
+		if (strings[count] && !(strings[count] = strdup(strings[count])))
+			out_of_memory("copy_section");
+	}
+}
 
-/***************************************************************************
-* add a new service to the services array initialising it with the given
-* service
-***************************************************************************/
-static int add_a_service(service *pservice, char *name)
+/* Initialise a section to the defaults. */
+static void init_section(local_vars *psection)
 {
-  int i;
-  service tservice;
-  int num_to_alloc = iNumServices+1;
+	memset(psection, 0, sizeof (local_vars));
+	copy_section(psection, &Vars.l);
+}
 
-  tservice = *pservice;
+/* Do a case-insensitive, whitespace-ignoring string compare. */
+static int strwicmp(char *psz1, char *psz2)
+{
+	/* if BOTH strings are NULL, return TRUE, if ONE is NULL return */
+	/* appropriate value. */
+	if (psz1 == psz2)
+		return 0;
+
+	if (psz1 == NULL)
+		return -1;
+
+	if (psz2 == NULL)
+		return 1;
+
+	/* sync the strings on first non-whitespace */
+	while (1) {
+		while (isSpace(psz1))
+			psz1++;
+		while (isSpace(psz2))
+			psz2++;
+		if (toUpper(psz1) != toUpper(psz2) || *psz1 == '\0' || *psz2 == '\0')
+			break;
+		psz1++;
+		psz2++;
+	}
+	return *psz1 - *psz2;
+}
 
-  /* it might already exist */
-  if (name)
-    {
-      i = getservicebyname(name,NULL);
-      if (i >= 0)
-	return(i);
-    }
+/* Find a section by name. Otherwise works like get_section. */
+static int getsectionbyname(char *name)
+{
+	int i;
 
-  i = iNumServices;
+	for (i = section_list.count - 1; i >= 0; i--) {
+		if (strwicmp(iSECTION(i).name, name) == 0)
+			break;
+	}
 
-  ServicePtrs = realloc_array(ServicePtrs, service *, num_to_alloc);
+	return i;
+}
 
-  if (ServicePtrs)
-	  pSERVICE(iNumServices) = new(service);
+/* Add a new section to the sections array w/the default values. */
+static int add_a_section(char *name)
+{
+	int i;
+	local_vars *s;
 
-  if (!ServicePtrs || !pSERVICE(iNumServices))
-	  return(-1);
+	/* it might already exist */
+	if (name) {
+		i = getsectionbyname(name);
+		if (i >= 0)
+			return i;
+	}
 
-  iNumServices++;
+	i = section_list.count;
+	s = EXPAND_ITEM_LIST(&section_list, local_vars, 2);
 
-  init_service(pSERVICE(i));
-  copy_service(pSERVICE(i),&tservice);
-  if (name)
-    string_set(&iSERVICE(i).name,name);
+	init_section(s);
+	if (name)
+		string_set(&s->name, name);
 
-  return(i);
+	return i;
 }
 
-/***************************************************************************
-* Do a case-insensitive, whitespace-ignoring string compare.
-***************************************************************************/
-static int strwicmp(char *psz1, char *psz2)
-{
-   /* if BOTH strings are NULL, return TRUE, if ONE is NULL return */
-   /* appropriate value. */
-   if (psz1 == psz2)
-      return (0);
-   else
-      if (psz1 == NULL)
-         return (-1);
-      else
-          if (psz2 == NULL)
-              return (1);
-
-   /* sync the strings on first non-whitespace */
-   while (1)
-   {
-      while (isSpace(psz1))
-         psz1++;
-      while (isSpace(psz2))
-         psz2++;
-      if (toUpper(psz1) != toUpper(psz2) || *psz1 == '\0' || *psz2 == '\0')
-         break;
-      psz1++;
-      psz2++;
-   }
-   return (*psz1 - *psz2);
-}
-
-/***************************************************************************
-* Map a parameter's string representation to something we can use.
-* Returns False if the parameter string is not recognised, else TRUE.
-***************************************************************************/
+/* Map a parameter's string representation to something we can use.
+ * Returns False if the parameter string is not recognised, else TRUE. */
 static int map_parameter(char *parmname)
 {
-   int iIndex;
+	int iIndex;
 
-   if (*parmname == '-')
-     return(-1);
+	if (*parmname == '-')
+		return -1;
 
-   for (iIndex = 0; parm_table[iIndex].label; iIndex++)
-      if (strwicmp(parm_table[iIndex].label, parmname) == 0)
-         return(iIndex);
+	for (iIndex = 0; parm_table[iIndex].label; iIndex++) {
+		if (strwicmp(parm_table[iIndex].label, parmname) == 0)
+			return iIndex;
+	}
 
-   rprintf(FLOG, "Unknown Parameter encountered: \"%s\"\n", parmname);
-   return(-1);
+	rprintf(FLOG, "Unknown Parameter encountered: \"%s\"\n", parmname);
+	return -1;
 }
 
-
-/***************************************************************************
-* Set a boolean variable from the text value stored in the passed string.
-* Returns True in success, False if the passed string does not correctly
-* represent a boolean.
-***************************************************************************/
+/* Set a boolean variable from the text value stored in the passed string.
+ * Returns True in success, False if the passed string does not correctly
+ * represent a boolean. */
 static BOOL set_boolean(BOOL *pb, char *parmvalue)
 {
-   BOOL bRetval;
+	if (strwicmp(parmvalue, "yes") == 0
+	 || strwicmp(parmvalue, "true") == 0
+	 || strwicmp(parmvalue, "1") == 0)
+		*pb = True;
+	else if (strwicmp(parmvalue, "no") == 0
+	      || strwicmp(parmvalue, "False") == 0
+	      || strwicmp(parmvalue, "0") == 0)
+		*pb = False;
+	else {
+		rprintf(FLOG, "Badly formed boolean in configuration file: \"%s\".\n", parmvalue);
+		return False;
+	}
+	return True;
+}
 
-   bRetval = True;
-   if (strwicmp(parmvalue, "yes") == 0 ||
-       strwicmp(parmvalue, "true") == 0 ||
-       strwicmp(parmvalue, "1") == 0)
-      *pb = True;
-   else
-      if (strwicmp(parmvalue, "no") == 0 ||
-          strwicmp(parmvalue, "False") == 0 ||
-          strwicmp(parmvalue, "0") == 0)
-         *pb = False;
-      else
-      {
-         rprintf(FLOG, "Badly formed boolean in configuration file: \"%s\".\n",
-               parmvalue);
-         bRetval = False;
-      }
-   return (bRetval);
-}
-
-/***************************************************************************
-* Find a service by name. Otherwise works like get_service.
-***************************************************************************/
-static int getservicebyname(char *name, service *pserviceDest)
-{
-   int iService;
-
-   for (iService = iNumServices - 1; iService >= 0; iService--)
-      if (strwicmp(iSERVICE(iService).name, name) == 0)
-      {
-         if (pserviceDest != NULL)
-	   copy_service(pserviceDest, pSERVICE(iService));
-         break;
-      }
-
-   return (iService);
-}
-
-
-
-/***************************************************************************
-* Copy a service structure to another
-***************************************************************************/
-static void copy_service(service *pserviceDest,
-                         service *pserviceSource)
-{
-  int i;
-
-  for (i=0;parm_table[i].label;i++)
-    if (parm_table[i].ptr && parm_table[i].class == P_LOCAL) {
-	void *def_ptr = parm_table[i].ptr;
-	void *src_ptr =
-	  ((char *)pserviceSource) + PTR_DIFF(def_ptr,&sDefault);
-	void *dest_ptr =
-	  ((char *)pserviceDest) + PTR_DIFF(def_ptr,&sDefault);
-
-	switch (parm_table[i].type)
-	  {
-	  case P_BOOL:
-	  case P_BOOLREV:
-	    *(BOOL *)dest_ptr = *(BOOL *)src_ptr;
-	    break;
-
-	  case P_INTEGER:
-	  case P_ENUM:
-	  case P_OCTAL:
-	    *(int *)dest_ptr = *(int *)src_ptr;
-	    break;
-
-	  case P_CHAR:
-	    *(char *)dest_ptr = *(char *)src_ptr;
-	    break;
-
-	  case P_PATH:
-	  case P_STRING:
-	    string_set(dest_ptr,*(char **)src_ptr);
-	    break;
-
-	  default:
-	    break;
-	  }
-      }
-}
-
-
-/***************************************************************************
-* Process a parameter for a particular service number. If snum < 0
-* then assume we are in the globals
-***************************************************************************/
-static BOOL lp_do_parameter(int snum, char *parmname, char *parmvalue)
-{
-   int parmnum, i;
-   void *parm_ptr=NULL; /* where we are going to store the result */
-   void *def_ptr=NULL;
-   char *cp;
-
-   parmnum = map_parameter(parmname);
-
-   if (parmnum < 0)
-     {
-       rprintf(FLOG, "IGNORING unknown parameter \"%s\"\n", parmname);
-       return(True);
-     }
-
-   def_ptr = parm_table[parmnum].ptr;
-
-   /* we might point at a service, the default service or a global */
-   if (snum < 0) {
-     parm_ptr = def_ptr;
-   } else {
-       if (parm_table[parmnum].class == P_GLOBAL) {
-	   rprintf(FLOG, "Global parameter %s found in service section!\n",parmname);
-	   return(True);
-	 }
-       parm_ptr = ((char *)pSERVICE(snum)) + PTR_DIFF(def_ptr,&sDefault);
-   }
-
-   /* now switch on the type of variable it is */
-   switch (parm_table[parmnum].type)
-     {
-     case P_BOOL:
-       set_boolean(parm_ptr,parmvalue);
-       break;
-
-     case P_BOOLREV:
-       set_boolean(parm_ptr,parmvalue);
-       *(BOOL *)parm_ptr = ! *(BOOL *)parm_ptr;
-       break;
-
-     case P_INTEGER:
-       *(int *)parm_ptr = atoi(parmvalue);
-       break;
-
-     case P_CHAR:
-       *(char *)parm_ptr = *parmvalue;
-       break;
-
-     case P_OCTAL:
-       sscanf(parmvalue,"%o",(int *)parm_ptr);
-       break;
-
-     case P_PATH:
-       string_set(parm_ptr,parmvalue);
-       if ((cp = *(char**)parm_ptr) != NULL) {
-	   int len = strlen(cp);
-	   while (len > 1 && cp[len-1] == '/') len--;
-	   cp[len] = '\0';
-       }
-       break;
-
-     case P_STRING:
-       string_set(parm_ptr,parmvalue);
-       break;
-
-     case P_GSTRING:
-       strlcpy((char *)parm_ptr,parmvalue,sizeof(pstring));
-       break;
-
-     case P_ENUM:
-	     for (i=0;parm_table[parmnum].enum_list[i].name;i++) {
-		     if (strequal(parmvalue, parm_table[parmnum].enum_list[i].name)) {
-			     *(int *)parm_ptr = parm_table[parmnum].enum_list[i].value;
-			     break;
-		     }
-	     }
-	     if (!parm_table[parmnum].enum_list[i].name) {
-		     if (atoi(parmvalue) > 0)
-			     *(int *)parm_ptr = atoi(parmvalue);
-	     }
-	     break;
-     case P_SEP:
-	     break;
-     }
-
-   return(True);
-}
-
-/***************************************************************************
-* Process a parameter.
-***************************************************************************/
+/* Process a parameter. */
 static BOOL do_parameter(char *parmname, char *parmvalue)
 {
-   return lp_do_parameter(bInGlobalSection?-2:iServiceIndex, parmname, parmvalue);
+	int parmnum, i;
+	void *parm_ptr; /* where we are going to store the result */
+	void *def_ptr;
+	char *cp;
+
+	parmnum = map_parameter(parmname);
+
+	if (parmnum < 0) {
+		rprintf(FLOG, "IGNORING unknown parameter \"%s\"\n", parmname);
+		return True;
+	}
+
+	def_ptr = parm_table[parmnum].ptr;
+
+	if (bInGlobalSection)
+		parm_ptr = def_ptr;
+	else {
+		if (parm_table[parmnum].class == P_GLOBAL) {
+			rprintf(FLOG, "Global parameter %s found in module section!\n", parmname);
+			return True;
+		}
+		parm_ptr = SECTION_PTR(&iSECTION(iSectionIndex), def_ptr);
+	}
+
+	/* now switch on the type of variable it is */
+	switch (parm_table[parmnum].type) {
+	case P_PATH:
+	case P_STRING:
+		/* delay expansion of vars */
+		break;
+	default:
+		/* expand any %VARS% now */
+		parmvalue = expand_vars(parmvalue);
+		break;
+	}
+
+	switch (parm_table[parmnum].type) {
+	case P_BOOL:
+		set_boolean(parm_ptr, parmvalue);
+		break;
+
+	case P_BOOLREV:
+		set_boolean(parm_ptr, parmvalue);
+		*(BOOL *)parm_ptr = ! *(BOOL *)parm_ptr;
+		break;
+
+	case P_INTEGER:
+		*(int *)parm_ptr = atoi(parmvalue);
+		break;
+
+	case P_CHAR:
+		*(char *)parm_ptr = *parmvalue;
+		break;
+
+	case P_OCTAL:
+		sscanf(parmvalue, "%o", (int *)parm_ptr);
+		break;
+
+	case P_PATH:
+		string_set(parm_ptr, parmvalue);
+		if ((cp = *(char**)parm_ptr) != NULL) {
+			int len = strlen(cp);
+			while (len > 1 && cp[len-1] == '/') len--;
+			cp[len] = '\0';
+		}
+		break;
+
+	case P_STRING:
+		string_set(parm_ptr, parmvalue);
+		break;
+
+	case P_ENUM:
+		for (i=0; parm_table[parmnum].enum_list[i].name; i++) {
+			if (strequal(parmvalue, parm_table[parmnum].enum_list[i].name)) {
+				*(int *)parm_ptr = parm_table[parmnum].enum_list[i].value;
+				break;
+			}
+		}
+		if (!parm_table[parmnum].enum_list[i].name) {
+			if (atoi(parmvalue) > 0)
+				*(int *)parm_ptr = atoi(parmvalue);
+		}
+		break;
+	}
+
+	return True;
 }
 
-/***************************************************************************
-* Process a new section (service). At this stage all sections are services.
-* Later we'll have special sections that permit server parameters to be set.
-* Returns True on success, False on failure.
-***************************************************************************/
+/* Process a new section (rsync module).
+ * Returns True on success, False on failure. */
 static BOOL do_section(char *sectionname)
 {
-   BOOL bRetval;
-   BOOL isglobal = (strwicmp(sectionname, GLOBAL_NAME) == 0);
-   bRetval = False;
-
-   /* if we were in a global section then do the local inits */
-   if (bInGlobalSection && !isglobal)
-     init_locals();
+	BOOL isglobal;
 
-   /* if we've just struck a global section, note the fact. */
-   bInGlobalSection = isglobal;
+	if (*sectionname == ']') { /* A special push/pop/reset directive from params.c */
+		bInGlobalSection = 1;
+		if (strcmp(sectionname+1, "push") == 0) {
+			all_vars *vp = EXPAND_ITEM_LIST(&Vars_stack, all_vars, 2);
+			memcpy(vp, &Vars, sizeof Vars);
+		} else if (strcmp(sectionname+1, "pop") == 0
+		 || strcmp(sectionname+1, "reset") == 0) {
+			all_vars *vp = ((all_vars*)Vars_stack.items) + Vars_stack.count - 1;
+			if (!Vars_stack.count)
+				return False;
+			memcpy(&Vars, vp, sizeof Vars);
+			if (sectionname[1] == 'p')
+				Vars_stack.count--;
+		} else
+			return False;
+		return True;
+	}
 
-   /* check for multiple global sections */
-   if (bInGlobalSection)
-   {
-     return(True);
-   }
+	isglobal = strwicmp(sectionname, GLOBAL_NAME) == 0;
 
-   if (strchr(sectionname, '/') != NULL) {
-     rprintf(FLOG, "Warning: invalid section name in configuration file: %s\n", sectionname);
-     return False;
-   }
+	/* At the end of the global section, add any --dparam items. */
+	if (bInGlobalSection && !isglobal) {
+		if (!section_list.count)
+			set_dparams(0);
+	}
 
-   /* if we have a current service, tidy it up before moving on */
-   bRetval = True;
+	/* if we've just struck a global section, note the fact. */
+	bInGlobalSection = isglobal;
 
-   if (iServiceIndex >= 0)
-     bRetval = True;
+	/* check for multiple global sections */
+	if (bInGlobalSection)
+		return True;
+
+#if 0
+	/* If we have a current section, tidy it up before moving on. */
+	if (iSectionIndex >= 0) {
+		/* Add any tidy work as needed ... */
+		if (problem)
+			return False;
+	}
+#endif
 
-   /* if all is still well, move to the next record in the services array */
-   if (bRetval)
-     {
-       /* We put this here to avoid an odd message order if messages are */
-       /* issued by the post-processing of a previous section. */
+	if (strchr(sectionname, '/') != NULL) {
+		rprintf(FLOG, "Warning: invalid section name in configuration file: %s\n", sectionname);
+		return False;
+	}
 
-       if ((iServiceIndex=add_a_service(&sDefault,sectionname)) < 0)
-	 {
-	   rprintf(FLOG, "Failed to add a new service\n");
-	   return(False);
-	 }
-     }
+	if ((iSectionIndex = add_a_section(sectionname)) < 0) {
+		rprintf(FLOG, "Failed to add a new module\n");
+		bInGlobalSection = True;
+		return False;
+	}
 
-   return (bRetval);
+	return True;
 }
 
-
-/***************************************************************************
-* Load the services array from the services file. Return True on success,
-* False on failure.
-***************************************************************************/
-BOOL lp_load(char *pszFname, int globals_only)
+/* Load the modules from the config file. Return True on success,
+ * False on failure. */
+int lp_load(char *pszFname, int globals_only)
 {
-	pstring n2;
-	BOOL bRetval;
-
-	bRetval = False;
-
 	bInGlobalSection = True;
 
-	init_globals();
-
-	pstrcpy(n2, pszFname);
+	reset_all_vars();
 
-	/* We get sections first, so have to start 'behind' to make up */
-	iServiceIndex = -1;
-	bRetval = pm_process(n2, globals_only?NULL:do_section, do_parameter);
+	/* We get sections first, so have to start 'behind' to make up. */
+	iSectionIndex = -1;
+	return pm_process(pszFname, globals_only ? NULL : do_section, do_parameter);
+}
+
+BOOL set_dparams(int syntax_check_only)
+{
+	char *equal, *val, **params = dparam_list.items;
+	unsigned j;
+
+	for (j = 0; j < dparam_list.count; j++) {
+		equal = strchr(params[j], '='); /* options.c verified this */
+		*equal = '\0';
+		if (syntax_check_only) {
+			if (map_parameter(params[j]) < 0) {
+				rprintf(FERROR, "Unknown parameter \"%s\"\n", params[j]);
+				*equal = '=';
+				return False;
+			}
+		} else {
+			for (val = equal+1; isSpace(val); val++) {}
+			do_parameter(params[j], val);
+		}
+		*equal = '=';
+	}
 
-	return (bRetval);
+	return True;
 }
 
-
-/***************************************************************************
-* return the max number of services
-***************************************************************************/
-int lp_numservices(void)
+/* Return the max number of modules (sections). */
+int lp_num_modules(void)
 {
-  return(iNumServices);
+	return section_list.count;
 }
 
-/***************************************************************************
-* Return the number of the service with the given name, or -1 if it doesn't
-* exist. Note that this is a DIFFERENT ANIMAL from the internal function
-* getservicebyname()! This works ONLY if all services have been loaded, and
-* does not copy the found service.
-***************************************************************************/
+/* Return the number of the module with the given name, or -1 if it doesn't
+ * exist. Note that this is a DIFFERENT ANIMAL from the internal function
+ * getsectionbyname()! This works ONLY if all sections have been loaded,
+ * and does not copy the found section. */
 int lp_number(char *name)
 {
-   int iService;
+	int i;
 
-   for (iService = iNumServices - 1; iService >= 0; iService--)
-      if (strcmp(lp_name(iService), name) == 0)
-         break;
+	for (i = section_list.count - 1; i >= 0; i--) {
+		if (strcmp(lp_name(i), name) == 0)
+			break;
+	}
 
-   return (iService);
+	return i;
 }
-
