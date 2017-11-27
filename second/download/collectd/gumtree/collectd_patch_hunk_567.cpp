         "admin", "password1");
 #endif
   }
 
   fprintf (stdout, "Creating %i values ... ", conf_num_values);
   fflush (stdout);
-  for (i = 0; i < conf_num_values; i++)
+  for (int i = 0; i < conf_num_values; i++)
   {
     lcc_value_list_t *vl;
 
     vl = create_value_list ();
     if (vl == NULL)
     {
