@@ -224,7 +224,7 @@ static int cliSendCommand(int argc, char **argv) {
     }
 
     if ((rc->arity > 0 && argc != rc->arity) ||
-        (rc->arity < 0 && argc < rc->arity)) {
+        (rc->arity < 0 && argc < -rc->arity)) {
             fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
             return 1;
     }