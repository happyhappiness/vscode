 #ifdef USE_HCACHE
   printf ("\nhcache backend: %s", mutt_hcache_backend ());
 #endif
 
   puts ("\n\nCompiler:");
   rstrip_in_place((char *)cc_version);
-  puts (cc_version);
+  puts ((char *)cc_version);
 
   rstrip_in_place((char *)configure_options);
-  printf ("\nConfigure options: %s\n", configure_options);
+  printf ("\nConfigure options: %s\n", (char *)configure_options);
 
   rstrip_in_place((char *)cc_cflags);
-  printf ("\nCompilation CFLAGS: %s\n", cc_cflags);
+  printf ("\nCompilation CFLAGS: %s\n", (char *)cc_cflags);
 
   puts (_("\nCompile options:"));
 
 #ifdef DOMAIN
   printf ("DOMAIN=\"%s\"\n", DOMAIN);
 #else
