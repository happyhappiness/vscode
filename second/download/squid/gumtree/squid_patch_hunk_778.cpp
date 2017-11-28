     if (Config.errorStylesheet) {
         ErrorPageFile tmpl("StylesSheet", ERR_MAX);
         tmpl.loadFromFile(Config.errorStylesheet);
         error_stylesheet.Printf("%s",tmpl.text());
     }
 
-#if USE_SSL
+#if USE_OPENSSL
     Ssl::errorDetailInitialize();
 #endif
 }
 
 void
 errorClean(void)
