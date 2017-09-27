         case 'v':
             printf("Server version: %s\n", ap_get_server_description());
             printf("Server built:   %s\n", ap_get_server_built());
             destroy_and_exit_process(process, 0);
 
         case 'V':
-            show_compile_settings();
-            destroy_and_exit_process(process, 0);
+            if (strcmp(ap_show_mpm(), "")) { /* MPM built-in? */
+                show_compile_settings();
+                destroy_and_exit_process(process, 0);
+            }
+            else {
+                showcompile = 1;
+            }
+            break;
 
         case 'l':
             ap_show_modules();
             destroy_and_exit_process(process, 0);
 
         case 'L':
