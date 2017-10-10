 
  fail:
 	send_client_data(3, abort_msg, sizeof(abort_msg));
 	die("git upload-pack: %s", abort_msg);
 }
 
-static int got_sha1(char *hex, unsigned char *sha1)
+static int got_sha1(const char *hex, unsigned char *sha1)
 {
 	struct object *o;
 	int we_knew_they_have = 0;
 
 	if (get_sha1_hex(hex, sha1))
 		die("git upload-pack: expected SHA1 object, got '%s'", hex);
