 			rsyserr(FERROR, errno, "pipe");
 			exit_cleanup(RERR_IPC);
 		}
 		batch_gen_fd = from_gen_pipe[0];
 		*f_out_p = from_gen_pipe[1];
 		*f_in_p = batch_fd;
-		ret = -1; /* no child pid */
+		pid = (pid_t)-1; /* no child pid */
 #ifdef ICONV_CONST
 		setup_iconv();
 #endif
 	} else if (local_server) {
 		/* If the user didn't request --[no-]whole-file, force
 		 * it on, but only if we're not batch processing. */
 		if (whole_file < 0 && !write_batch)
 			whole_file = 1;
 		set_allow_inc_recurse();
-		ret = local_child(argc, args, f_in_p, f_out_p, child_main);
+		pid = local_child(argc, args, f_in_p, f_out_p, child_main);
 #ifdef ICONV_CONST
 		setup_iconv();
 #endif
 	} else {
+		pid = piped_child(args, f_in_p, f_out_p);
 #ifdef ICONV_CONST
 		setup_iconv();
 #endif
-		if (protect_args) {
-			int fd;
-#ifdef ICONV_OPTION
-			int convert = ic_send != (iconv_t)-1;
-			xbuf outbuf, inbuf;
-
-			if (convert)
-				alloc_xbuf(&outbuf, 1024);
-#endif
-
-			ret = piped_child(args, f_in_p, f_out_p);
-
-			for (i = 0; args[i]; i++) {} /* find first NULL */
-			args[i] = "rsync"; /* set a new arg0 */
-			if (verbose > 1)
-				print_child_argv("protected args:", args + i + 1);
-			fd = *f_out_p;
-			do {
-#ifdef ICONV_OPTION
-				if (convert) {
-					INIT_XBUF_STRLEN(inbuf, args[i]);
-					iconvbufs(ic_send, &inbuf, &outbuf,
-						  ICB_EXPAND_OUT | ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
-					outbuf.buf[outbuf.len] = '\0';
-					write_buf(fd, outbuf.buf, outbuf.len + 1);
-					outbuf.len = 0;
-				} else
-#endif
-					write_buf(fd, args[i], strlen(args[i]) + 1);
-			} while (args[++i]);
-			write_byte(fd, 0);
-#ifdef ICONV_OPTION
-			if (convert)
-				free(outbuf.buf);
-#endif
-		} else
-			ret = piped_child(args, f_in_p, f_out_p);
+		if (protect_args)
+			send_protected_args(*f_out_p, args);
 	}
 
-	return ret;
+	return pid;
 
   oom:
 	out_of_memory("do_cmd");
 	return 0; /* not reached */
 }
 
