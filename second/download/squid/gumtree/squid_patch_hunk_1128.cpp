     if (!ret) {
         if (fatal_flag)
             fatalf("logfileOpen: %s: couldn't open!\n", path);
         else
             debugs(50, DBG_IMPORTANT, "logfileOpen: " << path << ": couldn't open!");
         lf->f_close(lf);
-        cbdataFree(lf);
+        delete lf;
         return NULL;
     }
     assert(lf->data != NULL);
 
     if (fatal_flag)
         lf->flags.fatal = 1;
