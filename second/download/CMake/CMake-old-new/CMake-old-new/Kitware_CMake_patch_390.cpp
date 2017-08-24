@@ -57,8 +57,6 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read.c 201157 2009-12-29 05:30:2
 
 static int	choose_filters(struct archive_read *);
 static int	choose_format(struct archive_read *);
-static void	free_filters(struct archive_read *);
-static int	close_filters(struct archive_read *);
 static struct archive_vtable *archive_read_vtable(void);
 static int64_t	_archive_filter_bytes(struct archive *, int);
 static int	_archive_filter_code(struct archive *, int);
@@ -194,14 +192,13 @@ client_skip_proxy(struct archive_read_filter *self, int64_t request)
 			int64_t get, ask = request;
 			if (ask > skip_limit)
 				ask = skip_limit;
-			get = (self->archive->client.skipper)(&self->archive->archive,
-			    self->data, ask);
+			get = (self->archive->client.skipper)
+				(&self->archive->archive, self->data, ask);
 			if (get == 0)
 				return (total);
 			request -= get;
 			total += get;
 		}
-		return total;
 	} else if (self->archive->client.seeker != NULL
 		&& request > 64 * 1024) {
 		/* If the client provided a seeker but not a skipper,
@@ -216,8 +213,8 @@ client_skip_proxy(struct archive_read_filter *self, int64_t request)
 		 * only do this for skips of over 64k.
 		 */
 		int64_t before = self->position;
-		int64_t after = (self->archive->client.seeker)(&self->archive->archive,
-		    self->data, request, SEEK_CUR);
+		int64_t after = (self->archive->client.seeker)
+		    (&self->archive->archive, self->data, request, SEEK_CUR);
 		if (after != before + request)
 			return ARCHIVE_FATAL;
 		return after - before;
@@ -242,14 +239,64 @@ client_seek_proxy(struct archive_read_filter *self, int64_t offset, int whence)
 static int
 client_close_proxy(struct archive_read_filter *self)
 {
-	int r = ARCHIVE_OK;
+	int r = ARCHIVE_OK, r2;
+	unsigned int i;
+
+	if (self->archive->client.closer == NULL)
+		return (r);
+	for (i = 0; i < self->archive->client.nodes; i++)
+	{
+		r2 = (self->archive->client.closer)
+			((struct archive *)self->archive,
+				self->archive->client.dataset[i].data);
+		if (r > r2)
+			r = r2;
+	}
+	return (r);
+}
 
-	if (self->archive->client.closer != NULL)
-		r = (self->archive->client.closer)((struct archive *)self->archive,
-		    self->data);
+static int
+client_open_proxy(struct archive_read_filter *self)
+{
+  int r = ARCHIVE_OK;
+	if (self->archive->client.opener != NULL)
+		r = (self->archive->client.opener)(
+		    (struct archive *)self->archive, self->data);
 	return (r);
 }
 
+static int
+client_switch_proxy(struct archive_read_filter *self, unsigned int iindex)
+{
+  int r1 = ARCHIVE_OK, r2 = ARCHIVE_OK;
+	void *data2 = NULL;
+
+	/* Don't do anything if already in the specified data node */
+	if (self->archive->client.cursor == iindex)
+		return (ARCHIVE_OK);
+
+	self->archive->client.cursor = iindex;
+	data2 = self->archive->client.dataset[self->archive->client.cursor].data;
+	if (self->archive->client.switcher != NULL)
+	{
+		r1 = r2 = (self->archive->client.switcher)
+			((struct archive *)self->archive, self->data, data2);
+		self->data = data2;
+	}
+	else
+	{
+		/* Attempt to call close and open instead */
+		if (self->archive->client.closer != NULL)
+			r1 = (self->archive->client.closer)
+				((struct archive *)self->archive, self->data);
+		self->data = data2;
+		if (self->archive->client.opener != NULL)
+			r2 = (self->archive->client.opener)
+				((struct archive *)self->archive, self->data);
+	}
+	return (r1 < r2) ? r1 : r2;
+}
+
 int
 archive_read_set_open_callback(struct archive *_a,
     archive_open_callback *client_opener)
@@ -306,21 +353,109 @@ archive_read_set_close_callback(struct archive *_a,
 }
 
 int
+archive_read_set_switch_callback(struct archive *_a,
+    archive_switch_callback *client_switcher)
+{
+	struct archive_read *a = (struct archive_read *)_a;
+	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
+	    "archive_read_set_switch_callback");
+	a->client.switcher = client_switcher;
+	return ARCHIVE_OK;
+}
+
+int
 archive_read_set_callback_data(struct archive *_a, void *client_data)
 {
+	return archive_read_set_callback_data2(_a, client_data, 0);
+}
+
+int
+archive_read_set_callback_data2(struct archive *_a, void *client_data,
+    unsigned int iindex)
+{
 	struct archive_read *a = (struct archive_read *)_a;
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
-	    "archive_read_set_callback_data");
-	a->client.data = client_data;
+	    "archive_read_set_callback_data2");
+
+	if (a->client.nodes == 0)
+	{
+		a->client.dataset = (struct archive_read_data_node *)
+		    calloc(1, sizeof(*a->client.dataset));
+		if (a->client.dataset == NULL)
+		{
+			archive_set_error(&a->archive, ENOMEM,
+				"No memory.");
+			return ARCHIVE_FATAL;
+		}
+		a->client.nodes = 1;
+	}
+
+	if (iindex > a->client.nodes - 1)
+	{
+		archive_set_error(&a->archive, EINVAL,
+			"Invalid index specified.");
+		return ARCHIVE_FATAL;
+	}
+	a->client.dataset[iindex].data = client_data;
+	a->client.dataset[iindex].begin_position = -1;
+	a->client.dataset[iindex].total_size = -1;
+	return ARCHIVE_OK;
+}
+
+int
+archive_read_add_callback_data(struct archive *_a, void *client_data,
+    unsigned int iindex)
+{
+	struct archive_read *a = (struct archive_read *)_a;
+	void *p;
+	unsigned int i;
+
+	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
+	    "archive_read_add_callback_data");
+	if (iindex > a->client.nodes) {
+		archive_set_error(&a->archive, EINVAL,
+			"Invalid index specified.");
+		return ARCHIVE_FATAL;
+	}
+	p = realloc(a->client.dataset, sizeof(*a->client.dataset)
+		* (++(a->client.nodes)));
+	if (p == NULL) {
+		archive_set_error(&a->archive, ENOMEM,
+			"No memory.");
+		return ARCHIVE_FATAL;
+	}
+	a->client.dataset = (struct archive_read_data_node *)p;
+	for (i = a->client.nodes - 1; i > iindex && i > 0; i--) {
+		a->client.dataset[i].data = a->client.dataset[i-1].data;
+		a->client.dataset[i].begin_position = -1;
+		a->client.dataset[i].total_size = -1;
+	}
+	a->client.dataset[iindex].data = client_data;
+	a->client.dataset[iindex].begin_position = -1;
+	a->client.dataset[iindex].total_size = -1;
 	return ARCHIVE_OK;
 }
 
 int
+archive_read_append_callback_data(struct archive *_a, void *client_data)
+{
+	struct archive_read *a = (struct archive_read *)_a;
+	return archive_read_add_callback_data(_a, client_data, a->client.nodes);
+}
+
+int
+archive_read_prepend_callback_data(struct archive *_a, void *client_data)
+{
+	return archive_read_add_callback_data(_a, client_data, 0);
+}
+
+int
 archive_read_open1(struct archive *_a)
 {
 	struct archive_read *a = (struct archive_read *)_a;
-	struct archive_read_filter *filter;
+	struct archive_read_filter *filter, *tmp;
 	int slot, e;
+	unsigned int i;
 
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
 	    "archive_read_open");
@@ -335,11 +470,14 @@ archive_read_open1(struct archive *_a)
 
 	/* Open data source. */
 	if (a->client.opener != NULL) {
-		e =(a->client.opener)(&a->archive, a->client.data);
+		e = (a->client.opener)(&a->archive, a->client.dataset[0].data);
 		if (e != 0) {
 			/* If the open failed, call the closer to clean up. */
-			if (a->client.closer)
-				(a->client.closer)(&a->archive, a->client.data);
+			if (a->client.closer) {
+				for (i = 0; i < a->client.nodes; i++)
+					(a->client.closer)(&a->archive,
+					    a->client.dataset[i].data);
+			}
 			return (e);
 		}
 	}
@@ -350,31 +488,51 @@ archive_read_open1(struct archive *_a)
 	filter->bidder = NULL;
 	filter->upstream = NULL;
 	filter->archive = a;
-	filter->data = a->client.data;
+	filter->data = a->client.dataset[0].data;
+	filter->open = client_open_proxy;
 	filter->read = client_read_proxy;
 	filter->skip = client_skip_proxy;
 	filter->seek = client_seek_proxy;
 	filter->close = client_close_proxy;
+	filter->sswitch = client_switch_proxy;
 	filter->name = "none";
-	filter->code = ARCHIVE_COMPRESSION_NONE;
-	a->filter = filter;
+	filter->code = ARCHIVE_FILTER_NONE;
 
-	/* Build out the input pipeline. */
-	e = choose_filters(a);
-	if (e < ARCHIVE_WARN) {
-		a->archive.state = ARCHIVE_STATE_FATAL;
-		return (ARCHIVE_FATAL);
+	a->client.dataset[0].begin_position = 0;
+	if (!a->filter || !a->bypass_filter_bidding)
+	{
+		a->filter = filter;
+		/* Build out the input pipeline. */
+		e = choose_filters(a);
+		if (e < ARCHIVE_WARN) {
+			a->archive.state = ARCHIVE_STATE_FATAL;
+			return (ARCHIVE_FATAL);
+		}
+	}
+	else
+	{
+		/* Need to add "NONE" type filter at the end of the filter chain */
+		tmp = a->filter;
+		while (tmp->upstream)
+			tmp = tmp->upstream;
+		tmp->upstream = filter;
 	}
 
-	slot = choose_format(a);
-	if (slot < 0) {
-		close_filters(a);
-		a->archive.state = ARCHIVE_STATE_FATAL;
-		return (ARCHIVE_FATAL);
+	if (!a->format)
+	{
+		slot = choose_format(a);
+		if (slot < 0) {
+			__archive_read_close_filters(a);
+			a->archive.state = ARCHIVE_STATE_FATAL;
+			return (ARCHIVE_FATAL);
+		}
+		a->format = &(a->formats[slot]);
 	}
-	a->format = &(a->formats[slot]);
 
 	a->archive.state = ARCHIVE_STATE_HEADER;
+
+	/* Ensure libarchive starts from the first node in a multivolume set */
+	client_switch_proxy(a->filter, 0);
 	return (e);
 }
 
@@ -414,8 +572,8 @@ choose_filters(struct archive_read *a)
 			/* Verify the filter by asking it for some data. */
 			__archive_read_filter_ahead(a->filter, 1, &avail);
 			if (avail < 0) {
-				close_filters(a);
-				free_filters(a);
+				__archive_read_close_filters(a);
+				__archive_read_free_filters(a);
 				return (ARCHIVE_FATAL);
 			}
 			a->archive.compression_name = a->filter->name;
@@ -433,8 +591,8 @@ choose_filters(struct archive_read *a)
 		a->filter = filter;
 		r = (best_bidder->init)(a->filter);
 		if (r != ARCHIVE_OK) {
-			close_filters(a);
-			free_filters(a);
+			__archive_read_close_filters(a);
+			__archive_read_free_filters(a);
 			return (ARCHIVE_FATAL);
 		}
 	}
@@ -502,6 +660,9 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 
 	a->read_data_output_offset = 0;
 	a->read_data_remaining = 0;
+	a->read_data_is_posix_read = 0;
+	a->read_data_requested = 0;
+	a->data_start_node = a->client.cursor;
 	/* EOF always wins; otherwise return the worst error. */
 	return (r2 < r1 || r2 == ARCHIVE_EOF) ? r2 : r1;
 }
@@ -612,6 +773,8 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 	while (s > 0) {
 		if (a->read_data_remaining == 0) {
 			read_buf = a->read_data_block;
+			a->read_data_is_posix_read = 1;
+			a->read_data_requested = s;
 			r = _archive_read_data_block(&a->archive, &read_buf,
 			    &a->read_data_remaining, &a->read_data_offset);
 			a->read_data_block = read_buf;
@@ -633,13 +796,13 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 		}
 
 		/* Compute the amount of zero padding needed. */
-		if (a->read_data_output_offset + s <
+		if (a->read_data_output_offset + (int64_t)s <
 		    a->read_data_offset) {
 			len = s;
 		} else if (a->read_data_output_offset <
 		    a->read_data_offset) {
-			len = a->read_data_offset -
-			    a->read_data_output_offset;
+			len = (size_t)(a->read_data_offset -
+			    a->read_data_output_offset);
 		} else
 			len = 0;
 
@@ -665,6 +828,8 @@ archive_read_data(struct archive *_a, void *buff, size_t s)
 			bytes_read += len;
 		}
 	}
+	a->read_data_is_posix_read = 0;
+	a->read_data_requested = 0;
 	return (bytes_read);
 }
 
@@ -699,6 +864,23 @@ archive_read_data_skip(struct archive *_a)
 	return (r);
 }
 
+int64_t
+archive_seek_data(struct archive *_a, int64_t offset, int whence)
+{
+	struct archive_read *a = (struct archive_read *)_a;
+	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_DATA,
+	    "archive_seek_data_block");
+
+	if (a->format->seek_data == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
+		    "Internal error: "
+		    "No format_seek_data_block function registered");
+		return (ARCHIVE_FATAL);
+	}
+
+	return (a->format->seek_data)(a, offset, whence);
+}
+
 /*
  * Read the next block of entry data from the archive.
  * This is a zero-copy interface; the client receives a pointer,
@@ -725,8 +907,8 @@ _archive_read_data_block(struct archive *_a,
 	return (a->format->read_data)(a, buff, size, offset);
 }
 
-static int
-close_filters(struct archive_read *a)
+int
+__archive_read_close_filters(struct archive_read *a)
 {
 	struct archive_read_filter *f = a->filter;
 	int r = ARCHIVE_OK;
@@ -746,8 +928,8 @@ close_filters(struct archive_read *a)
 	return r;
 }
 
-static void
-free_filters(struct archive_read *a)
+void
+__archive_read_free_filters(struct archive_read *a)
 {
 	while (a->filter != NULL) {
 		struct archive_read_filter *t = a->filter->upstream;
@@ -791,7 +973,7 @@ _archive_read_close(struct archive *_a)
 	/* TODO: Clean up the formatters. */
 
 	/* Release the filter objects. */
-	r1 = close_filters(a);
+	r1 = __archive_read_close_filters(a);
 	if (r1 < r)
 		r = r1;
 
@@ -830,7 +1012,7 @@ _archive_read_free(struct archive *_a)
 	}
 
 	/* Free the filters */
-	free_filters(a);
+	__archive_read_free_filters(a);
 
 	/* Release the bidder objects. */
 	n = sizeof(a->bidders)/sizeof(a->bidders[0]);
@@ -847,6 +1029,7 @@ _archive_read_free(struct archive *_a)
 		archive_entry_free(a->entry);
 	a->archive.magic = 0;
 	__archive_clean(&a->archive);
+	free(a->client.dataset);
 	free(a);
 	return (r);
 }
@@ -856,7 +1039,8 @@ get_filter(struct archive *_a, int n)
 {
 	struct archive_read *a = (struct archive_read *)_a;
 	struct archive_read_filter *f = a->filter;
-	/* We use n == -1 for 'the last filter', which is always the client proxy. */
+	/* We use n == -1 for 'the last filter', which is always the
+	 * client proxy. */
 	if (n == -1 && f != NULL) {
 		struct archive_read_filter *last = f;
 		f = f->upstream;
@@ -909,6 +1093,7 @@ __archive_read_register_format(struct archive_read *a,
     int (*read_header)(struct archive_read *, struct archive_entry *),
     int (*read_data)(struct archive_read *, const void **, size_t *, int64_t *),
     int (*read_data_skip)(struct archive_read *),
+    int64_t (*seek_data)(struct archive_read *, int64_t, int),
     int (*cleanup)(struct archive_read *))
 {
 	int i, number_slots;
@@ -928,6 +1113,7 @@ __archive_read_register_format(struct archive_read *a,
 			a->formats[i].read_header = read_header;
 			a->formats[i].read_data = read_data;
 			a->formats[i].read_data_skip = read_data_skip;
+			a->formats[i].seek_data = seek_data;
 			a->formats[i].cleanup = cleanup;
 			a->formats[i].data = format_data;
 			a->formats[i].name = name;
@@ -1074,7 +1260,8 @@ __archive_read_filter_ahead(struct archive_read_filter *filter,
 		if (filter->next > filter->buffer &&
 		    filter->next + min > filter->buffer + filter->buffer_size) {
 			if (filter->avail > 0)
-				memmove(filter->buffer, filter->next, filter->avail);
+				memmove(filter->buffer, filter->next,
+				    filter->avail);
 			filter->next = filter->buffer;
 		}
 
@@ -1089,15 +1276,26 @@ __archive_read_filter_ahead(struct archive_read_filter *filter,
 			    &filter->client_buff);
 			if (bytes_read < 0) {		/* Read error. */
 				filter->client_total = filter->client_avail = 0;
-				filter->client_next = filter->client_buff = NULL;
+				filter->client_next =
+				    filter->client_buff = NULL;
 				filter->fatal = 1;
 				if (avail != NULL)
 					*avail = ARCHIVE_FATAL;
 				return (NULL);
 			}
-			if (bytes_read == 0) {	/* Premature end-of-file. */
+			if (bytes_read == 0) {
+				/* Check for another client object first */
+				if (filter->archive->client.cursor !=
+				      filter->archive->client.nodes - 1) {
+					if (client_switch_proxy(filter,
+					    filter->archive->client.cursor + 1)
+					    == ARCHIVE_OK)
+						continue;
+				}
+				/* Premature end-of-file. */
 				filter->client_total = filter->client_avail = 0;
-				filter->client_next = filter->client_buff = NULL;
+				filter->client_next =
+				    filter->client_buff = NULL;
 				filter->end_of_file = 1;
 				/* Return whatever we do have. */
 				if (avail != NULL)
@@ -1107,9 +1305,7 @@ __archive_read_filter_ahead(struct archive_read_filter *filter,
 			filter->client_total = bytes_read;
 			filter->client_avail = filter->client_total;
 			filter->client_next = filter->client_buff;
-		}
-		else
-		{
+		} else {
 			/*
 			 * We can't satisfy the request from the copy
 			 * buffer or the existing client data, so we
@@ -1130,9 +1326,10 @@ __archive_read_filter_ahead(struct archive_read_filter *filter,
 					t *= 2;
 					if (t <= s) { /* Integer overflow! */
 						archive_set_error(
-							&filter->archive->archive,
-							ENOMEM,
-						    "Unable to allocate copy buffer");
+						    &filter->archive->archive,
+						    ENOMEM,
+						    "Unable to allocate copy"
+						    " buffer");
 						filter->fatal = 1;
 						if (avail != NULL)
 							*avail = ARCHIVE_FATAL;
@@ -1171,8 +1368,8 @@ __archive_read_filter_ahead(struct archive_read_filter *filter,
 			if (tocopy > filter->client_avail)
 				tocopy = filter->client_avail;
 
-			memcpy(filter->next + filter->avail, filter->client_next,
-			    tocopy);
+			memcpy(filter->next + filter->avail,
+			    filter->client_next, tocopy);
 			/* Remove this data from client buffer. */
 			filter->client_next += tocopy;
 			filter->client_avail -= tocopy;
@@ -1231,7 +1428,7 @@ advance_file_pointer(struct archive_read_filter *filter, int64_t request)
 
 	/* Use up the copy buffer first. */
 	if (filter->avail > 0) {
-		min = minimum(request, (int64_t)filter->avail);
+		min = (size_t)minimum(request, (int64_t)filter->avail);
 		filter->next += min;
 		filter->avail -= min;
 		request -= min;
@@ -1241,7 +1438,7 @@ advance_file_pointer(struct archive_read_filter *filter, int64_t request)
 
 	/* Then use up the client buffer. */
 	if (filter->client_avail > 0) {
-		min = minimum(request, (int64_t)filter->client_avail);
+		min = (size_t)minimum(request, (int64_t)filter->client_avail);
 		filter->client_next += min;
 		filter->client_avail -= min;
 		request -= min;
@@ -1275,6 +1472,13 @@ advance_file_pointer(struct archive_read_filter *filter, int64_t request)
 		}
 
 		if (bytes_read == 0) {
+			if (filter->archive->client.cursor !=
+			      filter->archive->client.nodes - 1) {
+				if (client_switch_proxy(filter,
+				    filter->archive->client.cursor + 1)
+				    == ARCHIVE_OK)
+					continue;
+			}
 			filter->client_buff = NULL;
 			filter->end_of_file = 1;
 			return (total_bytes_skipped);
@@ -1283,7 +1487,7 @@ advance_file_pointer(struct archive_read_filter *filter, int64_t request)
 		if (bytes_read >= request) {
 			filter->client_next =
 			    ((const char *)filter->client_buff) + request;
-			filter->client_avail = bytes_read - request;
+			filter->client_avail = (size_t)(bytes_read - request);
 			filter->client_total = bytes_read;
 			total_bytes_skipped += request;
 			filter->position += request;
@@ -1306,15 +1510,109 @@ __archive_read_seek(struct archive_read *a, int64_t offset, int whence)
 }
 
 int64_t
-__archive_read_filter_seek(struct archive_read_filter *filter, int64_t offset, int whence)
+__archive_read_filter_seek(struct archive_read_filter *filter, int64_t offset,
+    int whence)
 {
+	struct archive_read_client *client;
 	int64_t r;
+	unsigned int cursor;
 
 	if (filter->closed || filter->fatal)
 		return (ARCHIVE_FATAL);
 	if (filter->seek == NULL)
 		return (ARCHIVE_FAILED);
-	r = filter->seek(filter, offset, whence);
+
+	client = &(filter->archive->client);
+	switch (whence) {
+	case SEEK_CUR:
+		/* Adjust the offset and use SEEK_SET instead */
+		offset += filter->position;			
+	case SEEK_SET:
+		cursor = 0;
+		while (1)
+		{
+			if (client->dataset[cursor].begin_position < 0 ||
+			    client->dataset[cursor].total_size < 0 ||
+			    client->dataset[cursor].begin_position +
+			      client->dataset[cursor].total_size - 1 > offset ||
+			    cursor + 1 >= client->nodes)
+				break;
+			r = client->dataset[cursor].begin_position +
+				client->dataset[cursor].total_size;
+			client->dataset[++cursor].begin_position = r;
+		}
+		while (1) {
+			r = client_switch_proxy(filter, cursor);
+			if (r != ARCHIVE_OK)
+				return r;
+			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
+				return r;
+			client->dataset[cursor].total_size = r;
+			if (client->dataset[cursor].begin_position +
+			    client->dataset[cursor].total_size - 1 > offset ||
+			    cursor + 1 >= client->nodes)
+				break;
+			r = client->dataset[cursor].begin_position +
+				client->dataset[cursor].total_size;
+			client->dataset[++cursor].begin_position = r;
+		}
+		offset -= client->dataset[cursor].begin_position;
+		if (offset < 0)
+			offset = 0;
+		else if (offset > client->dataset[cursor].total_size - 1)
+			offset = client->dataset[cursor].total_size - 1;
+		if ((r = client_seek_proxy(filter, offset, SEEK_SET)) < 0)
+			return r;
+		break;
+
+	case SEEK_END:
+		cursor = 0;
+		while (1) {
+			if (client->dataset[cursor].begin_position < 0 ||
+			    client->dataset[cursor].total_size < 0 ||
+			    cursor + 1 >= client->nodes)
+				break;
+			r = client->dataset[cursor].begin_position +
+				client->dataset[cursor].total_size;
+			client->dataset[++cursor].begin_position = r;
+		}
+		while (1) {
+			r = client_switch_proxy(filter, cursor);
+			if (r != ARCHIVE_OK)
+				return r;
+			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
+				return r;
+			client->dataset[cursor].total_size = r;
+			r = client->dataset[cursor].begin_position +
+				client->dataset[cursor].total_size;
+			if (cursor + 1 >= client->nodes)
+				break;
+			client->dataset[++cursor].begin_position = r;
+		}
+		while (1) {
+			if (r + offset >=
+			    client->dataset[cursor].begin_position)
+				break;
+			offset += client->dataset[cursor].total_size;
+			if (cursor == 0)
+				break;
+			cursor--;
+			r = client->dataset[cursor].begin_position +
+				client->dataset[cursor].total_size;
+		}
+		offset = (r + offset) - client->dataset[cursor].begin_position;
+		if ((r = client_switch_proxy(filter, cursor)) != ARCHIVE_OK)
+			return r;
+		r = client_seek_proxy(filter, offset, SEEK_SET);
+		if (r < ARCHIVE_OK)
+			return r;
+		break;
+
+	default:
+		return (ARCHIVE_FATAL);
+	}
+	r += client->dataset[cursor].begin_position;
+
 	if (r >= 0) {
 		/*
 		 * Ouch.  Clearing the buffer like this hurts, especially