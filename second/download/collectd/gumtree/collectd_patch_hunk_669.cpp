   hostname = NULL;
   plugin = NULL;
   plugin_instance = NULL;
   type = NULL;
   type_instance = NULL;
 
-  vl.values_len = ds->ds_num;
-  vl.values = malloc(vl.values_len * sizeof(*vl.values));
-  if (vl.values == NULL) {
-    cmd_error(CMD_ERROR, err, "malloc failed.");
-    sfree(identifier_copy);
-    return (CMD_ERROR);
-  }
-
   ret_putval->raw_identifier = identifier_copy;
   if (ret_putval->raw_identifier == NULL) {
     cmd_error(CMD_ERROR, err, "malloc failed.");
     cmd_destroy_putval(ret_putval);
     sfree(vl.values);
     return (CMD_ERROR);
