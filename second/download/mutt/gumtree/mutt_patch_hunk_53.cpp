   printf ("System: %s %s", uts.sysname, uts.release);
 #endif
 
   printf (" (%s)", uts.machine);
 
 #ifdef NCURSES_VERSION
-  printf (" [using ncurses %s]", NCURSES_VERSION);
+  printf ("\nncurses: %s (compiled with %s)", curses_version(), NCURSES_VERSION);
 #elif defined(USE_SLANG_CURSES)
-  printf (" [using slang %d]", SLANG_VERSION);
+  printf ("\nslang: %d", SLANG_VERSION);
 #endif
 
+#ifdef _LIBICONV_VERSION
+  printf ("\nlibiconv: %d.%d", _LIBICONV_VERSION >> 8,
+	  _LIBICONV_VERSION & 0xff);
+#endif
+
+#ifdef HAVE_LIBIDN
+  printf ("\nlibidn: %s (compiled with %s)", stringprep_check_version (NULL), 
+	  STRINGPREP_VERSION);
+#endif
+
+#ifdef USE_HCACHE
+  printf ("\nhcache backend: %s", mutt_hcache_backend ());
+#endif
+
+  puts ("\n\nCompiler:");
+  rstrip_in_place((char *)cc_version);
+  puts (cc_version);
+
+  rstrip_in_place((char *)configure_options);
+  printf ("\nConfigure options: %s\n", configure_options);
+
+  rstrip_in_place((char *)cc_cflags);
+  printf ("\nCompilation CFLAGS: %s\n", cc_cflags);
+
   puts (_("\nCompile options:"));
 
 #ifdef DOMAIN
   printf ("DOMAIN=\"%s\"\n", DOMAIN);
 #else
   puts ("-DOMAIN");
