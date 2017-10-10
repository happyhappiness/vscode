 	char buffer[MAXCOMMAND];
 
 	while (1) {
 		size_t i;
 		if (!fgets(buffer, MAXCOMMAND - 1, stdin)) {
 			if (ferror(stdin))
-				die("Comammand input error");
+				die("Command input error");
 			exit(0);
 		}
 		/* Strip end of line characters. */
 		i = strlen(buffer);
 		while (i > 0 && isspace(buffer[i - 1]))
 			buffer[--i] = 0;
