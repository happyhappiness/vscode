             /* Prefix for nested multi bulks should grow with idxlen+2 spaces */
             memset(_prefixlen,' ',idxlen+2);
             _prefixlen[idxlen+2] = '\0';
             _prefix = sdscat(sdsnew(prefix),_prefixlen);
 
             /* Setup prefix format for every entry */
-            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%dd) ",idxlen);
+            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%ud) ",idxlen);
 
             for (i = 0; i < r->elements; i++) {
                 /* Don't use the prefix for the first element, as the parent
                  * caller already prepended the index number. */
                 out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);
 
