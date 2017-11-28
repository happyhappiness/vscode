     error_stylesheet.reset();
 
     // look for and load stylesheet into global MemBuf for it.
     if (Config.errorStylesheet) {
         ErrorPageFile tmpl("StylesSheet", ERR_MAX);
         tmpl.loadFromFile(Config.errorStylesheet);
-        error_stylesheet.Printf("%s",tmpl.text());
+        error_stylesheet.appendf("%s",tmpl.text());
     }
 
 #if USE_OPENSSL
     Ssl::errorDetailInitialize();
 #endif
 }
