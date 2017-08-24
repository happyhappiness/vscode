@@ -101,16 +101,17 @@ archive_read_new(void)
 {
 	struct archive_read *a;
 
-	a = (struct archive_read *)malloc(sizeof(*a));
+	a = (struct archive_read *)calloc(1, sizeof(*a));
 	if (a == NULL)
 		return (NULL);
-	memset(a, 0, sizeof(*a));
 	a->archive.magic = ARCHIVE_READ_MAGIC;
 
 	a->archive.state = ARCHIVE_STATE_NEW;
 	a->entry = archive_entry_new2(&a->archive);
 	a->archive.vtable = archive_read_vtable();
 
+	a->passphrases.last = &a->passphrases.first;
+
 	return (&a->archive);
 }
 
@@ -194,10 +195,12 @@ client_skip_proxy(struct archive_read_filter *self, int64_t request)
 				ask = skip_limit;
 			get = (self->archive->client.skipper)
 				(&self->archive->archive, self->data, ask);
-			if (get == 0)
+			total += get;
+			if (get == 0 || get == request)
 				return (total);
+			if (get > request)
+				return ARCHIVE_FATAL;
 			request -= get;
-			total += get;
 		}
 	} else if (self->archive->client.seeker != NULL
 		&& request > 64 * 1024) {
@@ -230,8 +233,11 @@ client_seek_proxy(struct archive_read_filter *self, int64_t offset, int whence)
 	 * other libarchive code that assumes a successful forward
 	 * seek means it can also seek backwards.
 	 */
-	if (self->archive->client.seeker == NULL)
+	if (self->archive->client.seeker == NULL) {
+		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
+		    "Current client reader does not support seeking a device");
 		return (ARCHIVE_FAILED);
+	}
 	return (self->archive->client.seeker)(&self->archive->archive,
 	    self->data, offset, whence);
 }
@@ -454,7 +460,7 @@ archive_read_open1(struct archive *_a)
 {
 	struct archive_read *a = (struct archive_read *)_a;
 	struct archive_read_filter *filter, *tmp;
-	int slot, e;
+	int slot, e = ARCHIVE_OK;
 	unsigned int i;
 
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
@@ -544,13 +550,13 @@ archive_read_open1(struct archive *_a)
 static int
 choose_filters(struct archive_read *a)
 {
-	int number_bidders, i, bid, best_bid;
+	int number_bidders, i, bid, best_bid, n;
 	struct archive_read_filter_bidder *bidder, *best_bidder;
 	struct archive_read_filter *filter;
 	ssize_t avail;
 	int r;
 
-	for (;;) {
+	for (n = 0; n < 25; ++n) {
 		number_bidders = sizeof(a->bidders) / sizeof(a->bidders[0]);
 
 		best_bid = 0;
@@ -596,6 +602,9 @@ choose_filters(struct archive_read *a)
 			return (ARCHIVE_FATAL);
 		}
 	}
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Input requires too many filters for decoding");
+	return (ARCHIVE_FATAL);
 }
 
 /*
@@ -658,16 +667,14 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		break;
 	}
 
-	a->read_data_output_offset = 0;
-	a->read_data_remaining = 0;
-	a->read_data_is_posix_read = 0;
-	a->read_data_requested = 0;
+	__archive_reset_read_data(&a->archive);
+
 	a->data_start_node = a->client.cursor;
 	/* EOF always wins; otherwise return the worst error. */
 	return (r2 < r1 || r2 == ARCHIVE_EOF) ? r2 : r1;
 }
 
-int
+static int
 _archive_read_next_header(struct archive *_a, struct archive_entry **entryp)
 {
 	int ret;
@@ -813,7 +820,7 @@ archive_read_format_capabilities(struct archive *_a)
 ssize_t
 archive_read_data(struct archive *_a, void *buff, size_t s)
 {
-	struct archive_read *a = (struct archive_read *)_a;
+	struct archive *a = (struct archive *)_a;
 	char	*dest;
 	const void *read_buf;
 	size_t	 bytes_read;
@@ -828,7 +835,7 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 			read_buf = a->read_data_block;
 			a->read_data_is_posix_read = 1;
 			a->read_data_requested = s;
-			r = _archive_read_data_block(&a->archive, &read_buf,
+			r = archive_read_data_block(a, &read_buf,
 			    &a->read_data_remaining, &a->read_data_offset);
 			a->read_data_block = read_buf;
 			if (r == ARCHIVE_EOF)
@@ -843,7 +850,7 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 		}
 
 		if (a->read_data_offset < a->read_data_output_offset) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Encountered out-of-order sparse blocks");
 			return (ARCHIVE_RETRY);
 		}
@@ -887,6 +894,21 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 }
 
 /*
+ * Reset the read_data_* variables, used for starting a new entry.
+ */
+void __archive_reset_read_data(struct archive * a)
+{
+	a->read_data_output_offset = 0;
+	a->read_data_remaining = 0;
+	a->read_data_is_posix_read = 0;
+	a->read_data_requested = 0;
+
+   /* extra resets, from rar.c */
+   a->read_data_block = NULL;
+   a->read_data_offset = 0;
+}
+
+/*
  * Skip over all remaining data in this entry.
  */
 int
@@ -953,7 +975,7 @@ _archive_read_data_block(struct archive *_a,
 	if (a->format->read_data == NULL) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
 		    "Internal error: "
-		    "No format_read_data_block function registered");
+		    "No format->read_data function registered");
 		return (ARCHIVE_FATAL);
 	}
 
@@ -1040,6 +1062,7 @@ static int
 _archive_read_free(struct archive *_a)
 {
 	struct archive_read *a = (struct archive_read *)_a;
+	struct archive_read_passphrase *p;
 	int i, n;
 	int slots;
 	int r = ARCHIVE_OK;
@@ -1077,9 +1100,20 @@ _archive_read_free(struct archive *_a)
 		}
 	}
 
+	/* Release passphrase list. */
+	p = a->passphrases.first;
+	while (p != NULL) {
+		struct archive_read_passphrase *np = p->next;
+
+		/* A passphrase should be cleaned. */
+		memset(p->passphrase, 0, strlen(p->passphrase));
+		free(p->passphrase);
+		free(p);
+		p = np;
+	}
+
 	archive_string_free(&a->archive.error_string);
-	if (a->entry)
-		archive_entry_free(a->entry);
+	archive_entry_free(a->entry);
 	a->archive.magic = 0;
 	__archive_clean(&a->archive);
 	free(a->client.dataset);
@@ -1451,6 +1485,8 @@ __archive_read_filter_consume(struct archive_read_filter * filter,
 {
 	int64_t skipped;
 
+	if (request < 0)
+		return ARCHIVE_FATAL;
 	if (request == 0)
 		return 0;
 