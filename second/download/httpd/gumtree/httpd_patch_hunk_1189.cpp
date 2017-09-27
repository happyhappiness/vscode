                 concurrency = atoi(optarg);
                 break;
             case 'b':
                 windowsize = atoi(optarg);
                 break;
             case 'i':
-                if (posting == 1)
-                err("Cannot mix POST and HEAD\n");
+                if (posting > 0)
+                err("Cannot mix POST/PUT and HEAD\n");
                 posting = -1;
                 break;
             case 'g':
                 gnuplot = strdup(optarg);
                 break;
             case 'd':
