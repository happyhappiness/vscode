 			autorebase = AUTOREBASE_LOCAL;
 		else if (!strcmp(value, "remote"))
 			autorebase = AUTOREBASE_REMOTE;
 		else if (!strcmp(value, "always"))
 			autorebase = AUTOREBASE_ALWAYS;
 		else
-			return error("Malformed value for %s", var);
+			return error("malformed value for %s", var);
 		return 0;
 	}
 
 	/* Add other config variables here and to Documentation/config.txt. */
 	return 0;
 }
