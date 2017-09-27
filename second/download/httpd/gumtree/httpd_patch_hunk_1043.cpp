     }
 
   while ((nextfile = readdirectory(dir)) != NULL)
     {
     int frc;
     sprintf(buffer, "%.512s%c%.128s", filename, sep, nextfile);
-    frc = grep_or_recurse(buffer, recurse, TRUE, FALSE);
+    frc = grep_or_recurse(buffer, dir_recurse, TRUE, FALSE);
     if (frc == 0 && rc == 1) rc = 0;
     }
 
   closedirectory(dir);
   return rc;
   }
 
 /* If the file is not a directory, or we are not recursing, scan it. If this is
-the first and only argument at top level, we don't show the file name.
-Otherwise, control is via the show_filenames variable. */
+the first and only argument at top level, we don't show the file name (unless
+we are only showing the file name). Otherwise, control is via the
+show_filenames variable. */
 
 in = fopen(filename, "r");
 if (in == NULL)
   {
   fprintf(stderr, "pcregrep: Failed to open %s: %s\n", filename, strerror(errno));
   return 2;
   }
 
-rc = pcregrep(in, (show_filenames && !only_one_at_top)? filename : NULL);
+rc = pcregrep(in, (filenames_only || (show_filenames && !only_one_at_top))?
+  filename : NULL);
 fclose(in);
 return rc;
 }
 
 
 
