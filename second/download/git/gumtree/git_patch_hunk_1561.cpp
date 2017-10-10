 			error("failed to apply delta");
 
 		free(delta_data);
 		free(external_base);
 	}
 
-	*final_type = type;
-	*final_size = size;
+	if (final_type)
+		*final_type = type;
+	if (final_size)
+		*final_size = size;
 
 	unuse_pack(&w_curs);
 
 	if (delta_stack != small_delta_stack)
 		free(delta_stack);
 
