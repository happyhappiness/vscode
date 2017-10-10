 			strbuf_release(&err);
 			goto failure;
 		}
 		cb.newlog = fdopen_lock_file(&reflog_lock, "w");
 		if (!cb.newlog) {
 			error("cannot fdopen %s (%s)",
-			      reflog_lock.filename.buf, strerror(errno));
+			      get_lock_file_path(&reflog_lock), strerror(errno));
 			goto failure;
 		}
 	}
 
 	(*prepare_fn)(refname, sha1, cb.policy_cb);
 	for_each_reflog_ent(refname, expire_reflog_ent, &cb);
