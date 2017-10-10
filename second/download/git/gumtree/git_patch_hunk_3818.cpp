 void close_all_packs(void)
 {
 	struct packed_git *p;
 
 	for (p = packed_git; p; p = p->next)
 		if (p->do_not_close)
-			die("BUG! Want to close pack marked 'do-not-close'");
+			die("BUG: want to close pack marked 'do-not-close'");
 		else
 			close_pack(p);
 }
 
 
 /*
