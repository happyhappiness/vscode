 			status |= error("no reflog for '%s'", argv[i]);
 			continue;
 		}
 
 		recno = strtoul(spec + 2, &ep, 10);
 		if (*ep == '}') {
-			cb.recno = -recno;
+			cb.cmd.recno = -recno;
 			for_each_reflog_ent(ref, count_reflog_ent, &cb);
 		} else {
-			cb.expire_total = approxidate(spec + 2);
+			cb.cmd.expire_total = approxidate(spec + 2);
 			for_each_reflog_ent(ref, count_reflog_ent, &cb);
-			cb.expire_total = 0;
+			cb.cmd.expire_total = 0;
 		}
 
-		status |= expire_reflog(ref, sha1, 0, &cb);
+		status |= reflog_expire(ref, sha1, flags,
+					reflog_expiry_prepare,
+					should_expire_reflog_ent,
+					reflog_expiry_cleanup,
+					&cb);
 		free(ref);
 	}
 	return status;
 }
 
 /*
