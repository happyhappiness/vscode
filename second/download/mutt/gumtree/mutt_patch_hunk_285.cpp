     }
 
   if (key->issuer_serial)
     {
       s = key->issuer_serial;
       if (s)
-        /* L10N: DOTFILL */
-	fprintf (fp, _("Serial-No .: 0x%s\n"), s);
+        fprintf (fp, "%*s0x%s\n", KeyInfoPadding[KIP_SERIAL_NO],
+                 _(KeyInfoPrompts[KIP_SERIAL_NO]), s);
     }
 
   if (key->issuer_name)
     {
       s = key->issuer_name;
       if (s)
 	{
-          /* L10N: DOTFILL */
-	  fprintf (fp, _("Issued By .: "));
+          fprintf (fp, "%*s", KeyInfoPadding[KIP_ISSUED_BY],
+                 _(KeyInfoPrompts[KIP_ISSUED_BY]));
 	  parse_and_print_user_id (fp, s);
 	  putc ('\n', fp);
 	}
     }
 
   /* For PGP we list all subkeys. */
