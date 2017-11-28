             PARSE_ERROR;
         }			/* End of var type switch */
 
         if (bufp == NULL)
             PARSE_ERROR;
 
-#ifdef DEBUG_VARS_DECODE
+#if DEBUG_VARS_DECODE
         printf("VARS:  Adding to list.\n");
 #endif
         /* Add variable to the list */
         *VarLastP = Var;
         VarLastP = &(Var->next_variable);
     }
