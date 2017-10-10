 		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_IF_ASKED;
 		return 0;
 	}
 	die("bad %s argument: %s", opt->long_name, arg);
 }
 
-static int feed_object(const unsigned char *sha1, int fd, int negative)
+static void feed_object(const unsigned char *sha1, FILE *fh, int negative)
 {
-	char buf[42];
-
 	if (negative && !has_sha1_file(sha1))
-		return 1;
+		return;
 
-	memcpy(buf + negative, sha1_to_hex(sha1), 40);
 	if (negative)
-		buf[0] = '^';
-	buf[40 + negative] = '\n';
-	return write_or_whine(fd, buf, 41 + negative, "send-pack: send refs");
+		putc('^', fh);
+	fputs(sha1_to_hex(sha1), fh);
+	putc('\n', fh);
 }
 
 /*
  * Make a pack stream and spit it out into file descriptor fd
  */
 static int pack_objects(int fd, struct ref *refs, struct sha1_array *extra, struct send_pack_args *args)
