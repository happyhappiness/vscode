 		pack_open_windows--;
 		p->windows = w->next;
 		free(w);
 	}
 }
 
+static int close_pack_fd(struct packed_git *p)
+{
+	if (p->pack_fd < 0)
+		return 0;
+
+	close(p->pack_fd);
+	pack_open_fds--;
+	p->pack_fd = -1;
+
+	return 1;
+}
+
+static void close_pack(struct packed_git *p)
+{
+	close_pack_windows(p);
+	close_pack_fd(p);
+	close_pack_index(p);
+}
+
+void close_all_packs(void)
+{
+	struct packed_git *p;
+
+	for (p = packed_git; p; p = p->next)
+		if (p->do_not_close)
+			die("BUG! Want to close pack marked 'do-not-close'");
+		else
+			close_pack(p);
+}
+
+
 /*
  * The LRU pack is the one with the oldest MRU window, preferring packs
  * with no used windows, or the oldest mtime if it has no windows allocated.
  */
 static void find_lru_pack(struct packed_git *p, struct packed_git **lru_p, struct pack_window **mru_w, int *accept_windows_inuse)
 {
