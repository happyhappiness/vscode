 	memcpy(argv + argc, con->finalArgv,
 		sizeof(*argv) * con->finalArgvCount);
 	argc += con->finalArgvCount;
     }
 
     if (con->leftovers != NULL && con->numLeftovers > 0) {
-#if 0
-	argv[argc++] = "--";
-#endif
 	memcpy(argv + argc, con->leftovers, sizeof(*argv) * con->numLeftovers);
 	argc += con->numLeftovers;
     }
 
     argv[argc] = NULL;
 
+  {
 #ifdef __hpux
+    int rc = setresgid(getgid(), getgid(),-1);
+    if (rc) return POPT_ERROR_ERRNO;
     rc = setresuid(getuid(), getuid(),-1);
     if (rc) return POPT_ERROR_ERRNO;
 #else
 /*
  * XXX " ... on BSD systems setuid() should be preferred over setreuid()"
  * XXX 	sez' Timur Bakeyev <mc@bat.ru>
  * XXX	from Norbert Warmuth <nwarmuth@privat.circular.de>
  */
 #if defined(HAVE_SETUID)
+    int rc = setgid(getgid());
+    if (rc) return POPT_ERROR_ERRNO;
     rc = setuid(getuid());
     if (rc) return POPT_ERROR_ERRNO;
 #elif defined (HAVE_SETREUID)
-    rc = setreuid(getuid(), getuid()); /*hlauer: not portable to hpux9.01 */
+    int rc = setregid(getgid(), getgid());
+    if (rc) return POPT_ERROR_ERRNO;
+    rc = setreuid(getuid(), getuid());
     if (rc) return POPT_ERROR_ERRNO;
 #else
     ; /* Can't drop privileges */
 #endif
 #endif
+  }
 
     if (argv[0] == NULL)
 	return POPT_ERROR_NOARG;
-#ifdef MYDEBUG
+
+#ifdef	MYDEBUG
+if (_popt_debug)
     {	const char ** avp;
 	fprintf(stderr, "==> execvp(%s) argv[%d]:", argv[0], argc);
 	for (avp = argv; *avp; avp++)
 	    fprintf(stderr, " '%s'", *avp);
 	fprintf(stderr, "\n");
     }
 #endif
 
-    rc = execvp(argv[0], (char *const *)argv);
+    execvp(argv[0], (char *const *)argv);
+
     return POPT_ERROR_ERRNO;
 }
+/*@=bounds =boundswrite @*/
 
+/*@-boundswrite@*/
 /*@observer@*/ /*@null@*/ static const struct poptOption *
 findOption(const struct poptOption * opt, /*@null@*/ const char * longName,
 		char shortName,
 		/*@null@*/ /*@out@*/ poptCallbackType * callback,
 		/*@null@*/ /*@out@*/ const void ** callbackData,
 		int singleDash)
