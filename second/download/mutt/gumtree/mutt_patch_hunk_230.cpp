 	  return 1;
       }
     }
     /* L10N:
        Means "The path you specified as the destination file is a directory."
        See the msgid "Save to file: " (alias.c, recvattach.c) */
-    else if ((rc = mutt_yesorno (_("File is a directory, save under it?"), M_YES)) != M_YES)
-      return (rc == M_NO) ? 1 : -1;
+    else if ((rc = mutt_yesorno (_("File is a directory, save under it?"), MUTT_YES)) != MUTT_YES)
+      return (rc == MUTT_NO) ? 1 : -1;
 
     strfcpy (tmp, mutt_basename (NONULL (attname)), sizeof (tmp));
     if (mutt_get_field (_("File under directory: "), tmp, sizeof (tmp),
-                                    M_FILE | M_CLEAR) != 0 || !tmp[0])
+                                    MUTT_FILE | MUTT_CLEAR) != 0 || !tmp[0])
       return (-1);
     mutt_concat_path (fname, path, tmp, flen);
   }
   
   if (*append == 0 && access (fname, F_OK) == 0)
   {
