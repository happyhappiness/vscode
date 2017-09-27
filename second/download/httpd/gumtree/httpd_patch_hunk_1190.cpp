                     posting = 1;
                 }
                 else if (postdata) {
                     exit(r);
                 }
                 break;
+            case 'u':
+                if (posting != 0)
+                    err("Cannot mix PUT and HEAD\n");
+                if (0 == (r = open_postfile(optarg))) {
+                    posting = 2;
+                }
+                else if (postdata) {
+                    exit(r);
+                }
+                break;
             case 'r':
                 recverrok = 1;
                 break;
             case 'v':
                 verbosity = atoi(optarg);
                 break;
