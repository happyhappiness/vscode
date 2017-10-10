 		return 0;
 
 	/* check if its a handle to a console output screen buffer */
 	if (!fd) {
 		if (!GetConsoleMode(hcon, &mode))
 			return 0;
+		/*
+		 * This code path is only reached if there is no console
+		 * attached to stdout/stderr, i.e. we will not need to output
+		 * any text to any console, therefore we might just as well
+		 * use black as foreground color.
+		 */
+		sbi.wAttributes = 0;
 	} else if (!GetConsoleScreenBufferInfo(hcon, &sbi))
 		return 0;
 
 	if (fd >= 0 && fd <= 2)
 		fd_is_interactive[fd] |= FD_CONSOLE;
 
