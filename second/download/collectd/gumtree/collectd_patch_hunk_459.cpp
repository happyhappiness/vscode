 	{
 		if (print_timestamp)
 			fprintf (fh, "[%s] %s%s\n", timestamp_str, level_str, msg);
 		else
 			fprintf (fh, "%s%s\n", level_str, msg);
 
-		if (do_close != 0)
+		if (do_close) {
 			fclose (fh);
+		} else {
+			fflush(fh);
+		}
 	}
 
 	pthread_mutex_unlock (&file_lock);
 
 	return;
 } /* void logfile_print */
