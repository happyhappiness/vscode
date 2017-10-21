 	shell_user = shell_machine;
 	shell_machine = p+1;
       }
     }
 
     if (verbose > 3) {
-      fprintf(FERROR,"cmd=%s machine=%s user=%s path=%s\n",
+      fprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
 	      shell_cmd?shell_cmd:"",
 	      shell_machine?shell_machine:"",
 	      shell_user?shell_user:"",
 	      shell_path?shell_path:"");
     }
     
