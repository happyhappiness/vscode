 	if (flags & RL_CONVERT) {
 		xbuf outbuf;
 		INIT_XBUF(outbuf, buf, 0, bufsiz);
 		iconv_buf.pos = 0;
 		iconv_buf.len = s - iconv_buf.buf;
 		iconvbufs(ic_recv, &iconv_buf, &outbuf,
-			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
+			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_INIT);
 		outbuf.buf[outbuf.len] = '\0';
 		return outbuf.len;
 	}
 #endif
 
 	return s - buf;
 }
 
 void read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
 	       char ***argv_p, int *argc_p, char **request_p)
 {
 	int maxargs = MAX_ARGS;
-	int dot_pos = 0;
-	int argc = 0;
+	int dot_pos = 0, argc = 0, request_len = 0;
 	char **argv, *p;
 	int rl_flags = (rl_nulls ? RL_EOL_NULLS : 0);
 
 #ifdef ICONV_OPTION
 	rl_flags |= (protect_args && ic_recv != (iconv_t)-1 ? RL_CONVERT : 0);
 #endif
 
 	if (!(argv = new_array(char *, maxargs)))
 		out_of_memory("read_args");
 	if (mod_name && !protect_args)
 		argv[argc++] = "rsyncd";
 
+	if (request_p)
+		*request_p = NULL;
+
 	while (1) {
 		if (read_line(f_in, buf, bufsiz, rl_flags) == 0)
 			break;
 
 		if (argc == maxargs-1) {
 			maxargs += MAX_ARGS;
 			if (!(argv = realloc_array(argv, char *, maxargs)))
 				out_of_memory("read_args");
 		}
 
 		if (dot_pos) {
-			if (request_p) {
-				*request_p = strdup(buf);
-				request_p = NULL;
+			if (request_p && request_len < 1024) {
+				int len = strlen(buf);
+				if (request_len)
+					request_p[0][request_len++] = ' ';
+				if (!(*request_p = realloc_array(*request_p, char, request_len + len + 1)))
+					out_of_memory("read_args");
+				memcpy(*request_p + request_len, buf, len + 1);
+				request_len += len;
 			}
 			if (mod_name)
 				glob_expand_module(mod_name, buf, &argv, &argc, &maxargs);
 			else
 				glob_expand(buf, &argv, &argc, &maxargs);
 		} else {
