@@ -56,6 +56,7 @@ struct uudecode {
 #define ST_READ_UU	1
 #define ST_UUEND	2
 #define ST_READ_BASE64	3
+#define ST_IGNORE	4
 };
 
 static int	uudecode_bidder_bid(struct archive_read_filter_bidder *,
@@ -88,6 +89,7 @@ archive_read_support_filter_uu(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	bidder->data = NULL;
+	bidder->name = "uu";
 	bidder->bid = uudecode_bidder_bid;
 	bidder->init = uudecode_bidder_init;
 	bidder->options = NULL;
@@ -377,7 +379,7 @@ uudecode_bidder_init(struct archive_read_filter *self)
 	void *out_buff;
 	void *in_buff;
 
-	self->code = ARCHIVE_COMPRESSION_UU;
+	self->code = ARCHIVE_FILTER_UU;
 	self->name = "uu";
 	self->read = uudecode_filter_read;
 	self->skip = NULL; /* not supported */
@@ -470,6 +472,10 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 	total = 0;
 	out = uudecode->out_buff;
 	ravail = avail_in;
+	if (uudecode->state == ST_IGNORE) {
+		used = avail_in;
+		goto finish;
+	}
 	if (uudecode->in_cnt) {
 		/*
 		 * If there is remaining data which is saved by
@@ -485,12 +491,18 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 		uudecode->in_cnt = 0;
 	}
 	for (;used < avail_in; d += llen, used += llen) {
-		int l, body;
+		int64_t l, body;
 
 		b = d;
 		len = get_line(b, avail_in - used, &nl);
 		if (len < 0) {
 			/* Non-ascii character is found. */
+			if (uudecode->state == ST_FIND_HEAD &&
+			    (uudecode->total > 0 || total > 0)) {
+				uudecode->state = ST_IGNORE;
+				used = avail_in;
+				goto finish;
+			}
 			archive_set_error(&self->archive->archive,
 			    ARCHIVE_ERRNO_MISC,
 			    "Insufficient compressed data");
@@ -507,7 +519,7 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 				return (ARCHIVE_FATAL);
 			if (uudecode->in_buff != b)
 				memmove(uudecode->in_buff, b, len);
-			uudecode->in_cnt = len;
+			uudecode->in_cnt = (int)len;
 			if (total == 0) {
 				/* Do not return 0; it means end-of-file.
 				 * We should try to read bytes more. */
@@ -545,7 +557,7 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 			break;
 		case ST_READ_UU:
 			if (total + len * 2 > OUT_BUFF_SIZE)
-				break;
+				goto finish;
 			body = len - nl;
 			if (!uuchar[*b] || body <= 0) {
 				archive_set_error(&self->archive->archive,
@@ -611,7 +623,7 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 			break;
 		case ST_READ_BASE64:
 			if (total + len * 2 > OUT_BUFF_SIZE)
-				break;
+				goto finish;
 			l = len - nl;
 			if (l >= 3 && b[0] == '=' && b[1] == '=' &&
 			    b[2] == '=') {
@@ -657,8 +669,10 @@ uudecode_filter_read(struct archive_read_filter *self, const void **buff)
 			break;
 		}
 	}
-
-	__archive_read_filter_consume(self->upstream, ravail);
+finish:
+	if (ravail < avail_in)
+		used -= avail_in - ravail;
+	__archive_read_filter_consume(self->upstream, used);
 
 	*buff = uudecode->out_buff;
 	uudecode->total += total;