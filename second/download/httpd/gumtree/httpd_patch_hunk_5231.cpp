             case 'i':
                 if (method != NO_METH)
                     err("Cannot mix HEAD with other methods\n");
                 method = HEAD;
                 break;
             case 'g':
-                gnuplot = strdup(opt_arg);
+                gnuplot = xstrdup(opt_arg);
                 break;
             case 'd':
                 percentile = 0;
                 break;
             case 'e':
-                csvperc = strdup(opt_arg);
+                csvperc = xstrdup(opt_arg);
                 break;
             case 'S':
                 confidence = 0;
                 break;
             case 's':
                 aprtimeout = apr_time_from_sec(atoi(opt_arg)); /* timeout value */
