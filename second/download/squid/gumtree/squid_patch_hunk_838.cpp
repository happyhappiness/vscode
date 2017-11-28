                 fatal("Need to add -DMALLOC_DBG when compiling to use -mX option");
 #endif
 
             }
             break;
 
-#if USE_WIN32_SERVICE
-
         case 'n':
             /** \par n
-             * Set global option opt_signal_service (to TRUE).
-             * Stores the additional parameter given in global WIN32_Service_name */
-            xfree(WIN32_Service_name);
-
-            WIN32_Service_name = xstrdup(optarg);
-
-            opt_signal_service = TRUE;
-
+             * Set global option opt_signal_service (to true).
+             * Stores the additional parameter given in global service_name */
+            if (optarg && *optarg != '\0') {
+                const SBuf t(optarg);
+                ::Parser::Tokenizer tok(t);
+                const CharacterSet chr = CharacterSet::ALPHA+CharacterSet::DIGIT;
+                if (!tok.prefix(service_name, chr))
+                    fatalf("Expected alphanumeric service name for the -n option but got: %s", optarg);
+                if (!tok.atEnd())
+                    fatalf("Garbage after alphanumeric service name in the -n option value: %s", optarg);
+                if (service_name.length() > 32)
+                    fatalf("Service name (-n option) must be limited to 32 characters but got %u", service_name.length());
+                opt_signal_service = true;
+            } else {
+                fatal("A service name is required for the -n option");
+            }
             break;
 
+#if USE_WIN32_SERVICE
+
         case 'r':
             /** \par r
              * Set global option opt_remove_service (to TRUE) */
             opt_remove_service = TRUE;
 
             break;
