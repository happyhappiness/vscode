         ret = logfile_mod_stdio_open(lf, patharg, bufsz, fatal_flag);
     }
     if (!ret) {
         if (fatal_flag)
             fatalf("logfileOpen: %s: couldn't open!\n", path);
         else
-            debugs(50, 1, "logfileOpen: " << path << ": couldn't open!");
+            debugs(50, DBG_IMPORTANT, "logfileOpen: " << path << ": couldn't open!");
         lf->f_close(lf);
         cbdataFree(lf);
         return NULL;
     }
     assert(lf->data != NULL);
 
