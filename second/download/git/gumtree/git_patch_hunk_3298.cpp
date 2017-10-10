 			break;
 		if (r < 0)
 			die_errno("read error from cache daemon");
 		write_or_die(1, in, r);
 		got_data = 1;
 	}
+	close(fd);
 	return got_data;
 }
 
 static void spawn_daemon(const char *socket)
 {
 	struct child_process daemon = CHILD_PROCESS_INIT;
