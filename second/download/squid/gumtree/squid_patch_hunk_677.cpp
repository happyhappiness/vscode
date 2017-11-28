             fprintf(stderr, "Broken domain-controller %s\n", d);
             free(d);
             continue;
         }
         *c= '\0';
         ++c;
-        new_dc = (dc *) malloc(sizeof(dc));
+        new_dc = static_cast<dc *>(xmalloc(sizeof(dc)));
         if (!new_dc) {
             fprintf(stderr, "Malloc error while parsing DC options\n");
             free(d);
             continue;
         }
         /* capitalize */
         uc(c);
         uc(d);
         ++numcontrollers;
         new_dc->domain = d;
         new_dc->controller = c;
         new_dc->dead = 0;
-        if (controllers == NULL) {	/* first controller */
+        if (controllers == NULL) {  /* first controller */
             controllers = new_dc;
             last_dc = new_dc;
         } else {
-            last_dc->next = new_dc;	/* can't be null */
+            last_dc->next = new_dc; /* can't be null */
             last_dc = new_dc;
         }
     }
     if (numcontrollers == 0) {
         fprintf(stderr, "You must specify at least one domain-controller!\n");
         usage();
         exit(1);
     }
-    last_dc->next = controllers;	/* close the queue, now it's circular */
+    last_dc->next = controllers;    /* close the queue, now it's circular */
 }
 
 /**
  * tries connecting to the domain controllers in the "controllers" ring,
  * with failover if the adequate option is specified.
  */
