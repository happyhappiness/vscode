                 csvperc = strdup(optarg);
                 break;
             case 'S':
                 confidence = 0;
                 break;
             case 'p':
-                if (posting != 0)
-                    err("Cannot mix POST and HEAD\n");
-                if (0 == (r = open_postfile(optarg))) {
-                    posting = 1;
-                }
-                else if (postdata) {
-                    exit(r);
+                if (method != NO_METH)
+                    err("Cannot mix POST with other methods\n");
+                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
+                    exit(1);
                 }
+                method = POST;
+                send_body = 1;
                 break;
             case 'u':
-                if (posting != 0)
-                    err("Cannot mix PUT and HEAD\n");
-                if (0 == (r = open_postfile(optarg))) {
-                    posting = 2;
-                }
-                else if (postdata) {
-                    exit(r);
+                if (method != NO_METH)
+                    err("Cannot mix PUT with other methods\n");
+                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
+                    exit(1);
                 }
+                method = PUT;
+                send_body = 1;
                 break;
             case 'r':
                 recverrok = 1;
                 break;
             case 'v':
                 verbosity = atoi(optarg);
