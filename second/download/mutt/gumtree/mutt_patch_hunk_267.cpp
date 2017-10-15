               fprintf (fp, "%s%s", delim, _("certification"));
               delim = _(", ");
             }
           putc ('\n', fp);
         }
     }
-
-  if (Locale)
-    setlocale (LC_TIME, "C");
 }
 
 
 /* Show detailed information about the selected key */
 static void 
 verify_key (crypt_key_t *key)
