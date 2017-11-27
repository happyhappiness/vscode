         }
         ++values_len;
 
         if (endptr == value) {
           fprintf(stderr, "ERROR: Failed to parse value as number: %s.\n",
                   argv[i]);
-          return (-1);
+          return -1;
         } else if ((endptr != NULL) && (*endptr != '\0')) {
           fprintf(stderr, "ERROR: Garbage after value: %s.\n", endptr);
-          return (-1);
+          return -1;
         }
 
         value = tmp;
       }
 
       assert(values_len >= 1);
       vl.values_len = values_len;
 
       status = lcc_putval(c, &vl);
       if (status != 0) {
         fprintf(stderr, "ERROR: %s\n", lcc_strerror(c));
-        return (-1);
+        return -1;
       }
     }
   }
 
   if (values_len == 0) {
     fprintf(stderr, "ERROR: putval: Missing value list(s).\n");
-    return (-1);
+    return -1;
   }
-  return (0);
+  return 0;
 } /* putval */
 
 int main(int argc, char **argv) {
   char address[1024] = "unix:" DEFAULT_SOCK;
 
   lcc_connection_t *c;
