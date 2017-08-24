@@ -1,5 +1,6 @@
 /*-
  * Copyright (c) 2007 Joerg Sonnenberger
+ * Copyright (c) 2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -53,7 +54,9 @@ __FBSDID("$FreeBSD$");
 
 #include "archive.h"
 #include "archive_private.h"
+#include "archive_string.h"
 #include "archive_read_private.h"
+#include "filter_fork.h"
 
 
 #if ARCHIVE_VERSION_NUMBER < 4000000
@@ -79,50 +82,13 @@ archive_read_support_filter_program(struct archive *a, const char *cmd)
 	return (archive_read_support_filter_program_signature(a, cmd, NULL, 0));
 }
 
-
-/* This capability is only available on POSIX systems. */
-#if (!defined(HAVE_PIPE) || !defined(HAVE_FCNTL) || \
-    !(defined(HAVE_FORK) || defined(HAVE_VFORK))) && (!defined(_WIN32) || defined(__CYGWIN__))
-
-/*
- * On non-Posix systems, allow the program to build, but choke if
- * this function is actually invoked.
- */
-int
-archive_read_support_filter_program_signature(struct archive *_a,
-    const char *cmd, const void *signature, size_t signature_len)
-{
-	(void)_a; /* UNUSED */
-	(void)cmd; /* UNUSED */
-	(void)signature; /* UNUSED */
-	(void)signature_len; /* UNUSED */
-
-	archive_set_error(_a, -1,
-	    "External compression programs not supported on this platform");
-	return (ARCHIVE_FATAL);
-}
-
-int
-__archive_read_program(struct archive_read_filter *self, const char *cmd)
-{
-	(void)self; /* UNUSED */
-	(void)cmd; /* UNUSED */
-
-	archive_set_error(&self->archive->archive, -1,
-	    "External compression programs not supported on this platform");
-	return (ARCHIVE_FATAL);
-}
-
-#else
-
-#include "filter_fork.h"
-
 /*
  * The bidder object stores the command and the signature to watch for.
  * The 'inhibit' entry here is used to ensure that unchecked filters never
  * bid twice in the same pipeline.
  */
 struct program_bidder {
+	char *description;
 	char *cmd;
 	void *signature;
 	size_t signature_len;
@@ -138,8 +104,12 @@ static int	program_bidder_free(struct archive_read_filter_bidder *);
  * The actual filter needs to track input and output data.
  */
 struct program_filter {
-	char		*description;
+	struct archive_string description;
+#if defined(_WIN32) && !defined(__CYGWIN__)
+	HANDLE		 child;
+#else
 	pid_t		 child;
+#endif
 	int		 exit_status;
 	int		 waitpid_return;
 	int		 child_stdin, child_stdout;
@@ -151,6 +121,29 @@ struct program_filter {
 static ssize_t	program_filter_read(struct archive_read_filter *,
 		    const void **);
 static int	program_filter_close(struct archive_read_filter *);
+static void	free_state(struct program_bidder *);
+
+static int
+set_bidder_signature(struct archive_read_filter_bidder *bidder,
+    struct program_bidder *state, const void *signature, size_t signature_len)
+{
+
+	if (signature != NULL && signature_len > 0) {
+		state->signature_len = signature_len;
+		state->signature = malloc(signature_len);
+		memcpy(state->signature, signature, signature_len);
+	}
+
+	/*
+	 * Fill in the bidder object.
+	 */
+	bidder->data = state;
+	bidder->bid = program_bidder_bid;
+	bidder->init = program_bidder_init;
+	bidder->options = NULL;
+	bidder->free = program_bidder_free;
+	return (ARCHIVE_OK);
+}
 
 int
 archive_read_support_filter_program_signature(struct archive *_a,
@@ -169,37 +162,40 @@ archive_read_support_filter_program_signature(struct archive *_a,
 	/*
 	 * Allocate our private state.
 	 */
-	state = (struct program_bidder *)calloc(sizeof (*state), 1);
+	state = (struct program_bidder *)calloc(1, sizeof (*state));
 	if (state == NULL)
-		return (ARCHIVE_FATAL);
+		goto memerr;
 	state->cmd = strdup(cmd);
-	if (signature != NULL && signature_len > 0) {
-		state->signature_len = signature_len;
-		state->signature = malloc(signature_len);
-		memcpy(state->signature, signature, signature_len);
-	}
+	if (state->cmd == NULL)
+		goto memerr;
 
-	/*
-	 * Fill in the bidder object.
-	 */
-	bidder->data = state;
-	bidder->bid = program_bidder_bid;
-	bidder->init = program_bidder_init;
-	bidder->options = NULL;
-	bidder->free = program_bidder_free;
-	return (ARCHIVE_OK);
+	return set_bidder_signature(bidder, state, signature, signature_len);
+memerr:
+	free_state(state);
+	archive_set_error(_a, ENOMEM, "Can't allocate memory");
+	return (ARCHIVE_FATAL);
 }
 
 static int
 program_bidder_free(struct archive_read_filter_bidder *self)
 {
 	struct program_bidder *state = (struct program_bidder *)self->data;
-	free(state->cmd);
-	free(state->signature);
-	free(self->data);
+
+	free_state(state);
 	return (ARCHIVE_OK);
 }
 
+static void
+free_state(struct program_bidder *state)
+{
+
+	if (state) {
+		free(state->cmd);
+		free(state->signature);
+		free(state);
+	}
+}
+
 /*
  * If we do have a signature, bid only if that matches.
  *
@@ -258,6 +254,9 @@ child_stop(struct archive_read_filter *self, struct program_filter *state)
 			state->waitpid_return
 			    = waitpid(state->child, &state->exit_status, 0);
 		} while (state->waitpid_return == -1 && errno == EINTR);
+#if defined(_WIN32) && !defined(__CYGWIN__)
+		CloseHandle(state->child);
+#endif
 		state->child = 0;
 	}
 
@@ -310,11 +309,35 @@ child_read(struct archive_read_filter *self, char *buf, size_t buf_len)
 	struct program_filter *state = self->data;
 	ssize_t ret, requested, avail;
 	const char *p;
+#if defined(_WIN32) && !defined(__CYGWIN__)
+	HANDLE handle = (HANDLE)_get_osfhandle(state->child_stdout);
+#endif
 
 	requested = buf_len > SSIZE_MAX ? SSIZE_MAX : buf_len;
 
 	for (;;) {
 		do {
+#if defined(_WIN32) && !defined(__CYGWIN__)
+			/* Avoid infinity wait.
+			 * Note: If there is no data in the pipe, ReadFile()
+			 * called in read() never returns and so we won't
+			 * write remaining encoded data to the pipe.
+			 * Note: This way may cause performance problem.
+			 * we are looking forward to great code to resolve
+			 * this.  */
+			DWORD pipe_avail = -1;
+			int cnt = 2;
+
+			while (PeekNamedPipe(handle, NULL, 0, NULL,
+			    &pipe_avail, NULL) != 0 && pipe_avail == 0 &&
+			    cnt--)
+				Sleep(5);
+			if (pipe_avail == 0) {
+				ret = -1;
+				errno = EAGAIN;
+				break;
+			}
+#endif
 			ret = read(state->child_stdout, buf, requested);
 		} while (ret == -1 && errno == EINTR);
 
@@ -376,38 +399,57 @@ __archive_read_program(struct archive_read_filter *self, const char *cmd)
 	struct program_filter	*state;
 	static const size_t out_buf_len = 65536;
 	char *out_buf;
-	char *description;
 	const char *prefix = "Program: ";
+	pid_t child;
+	size_t l;
 
+	l = strlen(prefix) + strlen(cmd) + 1;
 	state = (struct program_filter *)calloc(1, sizeof(*state));
 	out_buf = (char *)malloc(out_buf_len);
-	description = (char *)malloc(strlen(prefix) + strlen(cmd) + 1);
-	if (state == NULL || out_buf == NULL || description == NULL) {
+	if (state == NULL || out_buf == NULL ||
+	    archive_string_ensure(&state->description, l) == NULL) {
 		archive_set_error(&self->archive->archive, ENOMEM,
 		    "Can't allocate input data");
-		free(state);
+		if (state != NULL) {
+			archive_string_free(&state->description);
+			free(state);
+		}
 		free(out_buf);
-		free(description);
 		return (ARCHIVE_FATAL);
 	}
+	archive_strcpy(&state->description, prefix);
+	archive_strcat(&state->description, cmd);
 
-	self->code = ARCHIVE_COMPRESSION_PROGRAM;
-	state->description = description;
-	strcpy(state->description, prefix);
-	strcat(state->description, cmd);
-	self->name = state->description;
+	self->code = ARCHIVE_FILTER_PROGRAM;
+	self->name = state->description.s;
 
 	state->out_buf = out_buf;
 	state->out_buf_len = out_buf_len;
 
-	if ((state->child = __archive_create_child(cmd,
-		 &state->child_stdin, &state->child_stdout)) == -1) {
+	child = __archive_create_child(cmd, &state->child_stdin,
+	    &state->child_stdout);
+	if (child == -1) {
+		free(state->out_buf);
+		free(state);
+		archive_set_error(&self->archive->archive, EINVAL,
+		    "Can't initialize filter; unable to run program \"%s\"",
+		    cmd);
+		return (ARCHIVE_FATAL);
+	}
+#if defined(_WIN32) && !defined(__CYGWIN__)
+	state->child = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, child);
+	if (state->child == NULL) {
+		child_stop(self, state);
 		free(state->out_buf);
 		free(state);
 		archive_set_error(&self->archive->archive, EINVAL,
-		    "Can't initialize filter; unable to run program \"%s\"", cmd);
+		    "Can't initialize filter; unable to run program \"%s\"",
+		    cmd);
 		return (ARCHIVE_FATAL);
 	}
+#else
+	state->child = child;
+#endif
 
 	self->data = state;
 	self->read = program_filter_read;
@@ -467,10 +509,8 @@ program_filter_close(struct archive_read_filter *self)
 
 	/* Release our private data. */
 	free(state->out_buf);
-	free(state->description);
+	archive_string_free(&state->description);
 	free(state);
 
 	return (e);
 }
-
-#endif /* !defined(HAVE_PIPE) || !defined(HAVE_VFORK) || !defined(HAVE_FCNTL) */