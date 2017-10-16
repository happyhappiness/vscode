       config->use_resume=TRUE;
       break;
     case 'd':
       /* postfield data */
       {
         char *postdata=NULL;
+        FILE *file;
 
-        if('@' == *nextarg) {
+        if(subletter == 'e') { /* --data-urlencode*/
+          /* [name]=[content], we encode the content part only
+           * [name]@[file name]
+           *
+           * Case 2: we first load the file using that name and then encode
+           * the content.
+           */
+          char *p = strchr(nextarg, '=');
+          size_t size = 0;
+          size_t nlen;
+          char is_file;
+          if(!p)
+            /* there was no '=' letter, check for a '@' instead */
+            p = strchr(nextarg, '@');
+          if (p) {
+            nlen = p - nextarg; /* length of the name part */
+            is_file = *p++; /* pass the separator */
+          }
+          else {
+            /* neither @ nor =, so no name and it isn't a file */
+            nlen = is_file = 0;
+            p = nextarg;
+          }
+          if('@' == is_file) {
+            /* a '@' letter, it means that a file name or - (stdin) follows */
+
+            if(curlx_strequal("-", p)) {
+              file = stdin;
+              SET_BINMODE(stdin);
+            }
+            else {
+              file = fopen(p, "rb");
+              if(!file)
+                warnf(config,
+                      "Couldn't read data from file \"%s\", this makes "
+                      "an empty POST.\n", nextarg);
+            }
+
+            err = file2memory(&postdata, &size, file);
+
+            if(file && (file != stdin))
+              fclose(file);
+            if(err)
+              return err;
+          }
+          else {
+            GetStr(&postdata, p);
+            size = strlen(postdata);
+          }
+
+          if(!postdata) {
+            /* no data from the file, point to a zero byte string to make this
+               get sent as a POST anyway */
+            postdata=strdup("");
+          }
+          else {
+            char *enc = curl_easy_escape(config->easy, postdata, size);
+            if(enc) {
+              /* now make a string with the name from above and append the
+                 encoded string */
+              size_t outlen = nlen + strlen(enc) + 2;
+              char *n = malloc(outlen);
+              if(!n)
+                return PARAM_NO_MEM;
+              if (nlen > 0) /* only append '=' if we have a name */
+                snprintf(n, outlen, "%.*s=%s", nlen, nextarg, enc);
+              else
+                strcpy(n, enc);
+              curl_free(enc);
+              free(postdata);
+              if(n) {
+                postdata = n;
+              }
+              else
+                return PARAM_NO_MEM;
+            }
+            else
+              return PARAM_NO_MEM;
+          }
+        }
+        else if('@' == *nextarg) {
+          size_t size = 0;
           /* the data begins with a '@' letter, it means that a file name
              or - (stdin) follows */
-          FILE *file;
-
           nextarg++; /* pass the @ */
 
           if(curlx_strequal("-", nextarg)) {
             file = stdin;
             if(subletter == 'b') /* forced data-binary */
               SET_BINMODE(stdin);
