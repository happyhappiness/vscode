     multi = multi_start;
     multi_start = multi_start->next;
     free (multi);
   }
 }
 
+/* Print list of OpenSSL engines supported.
+ */
+static void list_engines (const struct curl_slist *engines)
+{
+  puts ("Build-time engines:");
+  if (!engines) {
+    puts ("  <none>");
+    return;
+  }
+  for ( ; engines; engines = engines->next)
+    printf ("  %s\n", engines->data);
+}
+
 /***************************************************************************
  *
  * formparse()
  *
  * Reads a 'name=value' paramter and builds the appropriate linked list.
  *
