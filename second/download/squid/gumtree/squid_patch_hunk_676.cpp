     /* Okay, now begin filling controllers up */
     /* we can avoid memcpy-ing, and just reuse argv[] */
     for (j = optind; j < argc; ++j) {
         char *d, *c;
         /* d will not be freed in case of non-error. Since we don't reconfigure,
          * it's going to live as long as the process anyways */
-        d = (char*)malloc(strlen(argv[j]) + 1);
+        d = static_cast<char*>(xmalloc(strlen(argv[j]) + 1));
         strcpy(d, argv[j]);
         debug("Adding domain-controller %s\n", d);
         if (NULL == (c = strchr(d, '\\')) && NULL == (c = strchr(d, '/'))) {
             fprintf(stderr, "Couldn't grok domain-controller %s\n", d);
             free(d);
             continue;
