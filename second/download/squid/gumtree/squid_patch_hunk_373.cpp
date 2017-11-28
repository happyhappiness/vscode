         if (ret != 0)
             fatalf("parseConfigFile: '%s' failed with exit code %d\n", file_name, ret);
     } else {
         fclose(fp);
     }
 
-    cfg_filename = orig_cfg_filename;
+    SetConfigFilename(orig_cfg_filename, false);
     config_lineno = orig_config_lineno;
 
     xfree(tmp_line);
     return err_count;
 }
 
