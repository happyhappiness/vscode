@@ -27,6 +27,7 @@ main(int           const argc,
     xmlrpc_env env;
     xmlrpc_value *result;
     char *state_name;
+    int cc;
 
     if (argc-1 > 0) {
         fprintf(stderr, "No arguments");
@@ -40,15 +41,18 @@ main(int           const argc,
     xmlrpc_env_init(&env);
 
     /* Call the famous server at UserLand. */
-    result = xmlrpc_client_call(&env, "http://betty.userland.com/RPC2",
+    for ( cc = 30; cc < 35; cc ++ )
+      {
+      result = xmlrpc_client_call(&env, "http://betty.userland.com/RPC2",
         "examples.getStateName",
-        "(i)", (xmlrpc_int32) 41);
-    die_if_fault_occurred(&env);
-    
-    /* Get our state name and print it out. */
-    xmlrpc_parse_value(&env, result, "s", &state_name);
-    die_if_fault_occurred(&env);
-    printf("%s\n", state_name);
+        "(i)", (xmlrpc_int32) cc);
+      die_if_fault_occurred(&env);
+
+      /* Get our state name and print it out. */
+      xmlrpc_parse_value(&env, result, "s", &state_name);
+      die_if_fault_occurred(&env);
+      printf("%d: %s\n", cc, state_name);
+      }
     
     /* Dispose of our result value. */
     xmlrpc_DECREF(result);