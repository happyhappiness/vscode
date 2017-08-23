@@ -43,8 +43,6 @@ __FBSDID("$FreeBSD$");
 #endif
 #if HAVE_LZMA_H
 #include <lzma.h>
-#elif HAVE_LZMADEC_H
-#include <lzmadec.h>
 #endif
 
 #include "archive.h"
@@ -82,19 +80,6 @@ static ssize_t	xz_filter_read(struct archive_read_filter *, const void **);
 static int	xz_filter_close(struct archive_read_filter *);
 static int	xz_lzma_bidder_init(struct archive_read_filter *);
 
-#elif HAVE_LZMADEC_H && HAVE_LIBLZMADEC
-
-struct private_data {
-	lzmadec_stream	 stream;
-	unsigned char	*out_block;
-	size_t		 out_block_size;
-	int64_t		 total_out;
-	char		 eof; /* True = found end of compressed data. */
-};
-
-/* Lzma-only filter */
-static ssize_t	lzma_filter_read(struct archive_read_filter *, const void **);
-static int	lzma_filter_close(struct archive_read_filter *);
 #endif
 
 /*
@@ -178,8 +163,6 @@ archive_read_support_filter_lzma(struct archive *_a)
 	bidder->free = NULL;
 #if HAVE_LZMA_H && HAVE_LIBLZMA
 	return (ARCHIVE_OK);
-#elif HAVE_LZMADEC_H && HAVE_LIBLZMADEC
-	return (ARCHIVE_OK);
 #else
 	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
 	    "Using external lzma program for lzma decompression");
@@ -310,7 +293,7 @@ lzma_bidder_bid(struct archive_read_filter_bidder *self,
 	/* Second through fifth bytes are dictionary size, stored in
 	 * little-endian order. The minimum dictionary size is
 	 * 1 << 12(4KiB) which the lzma of LZMA SDK uses with option
-	 * -d12 and the maxinam dictionary size is 1 << 27(128MiB)
+	 * -d12 and the maximum dictionary size is 1 << 27(128MiB)
 	 * which the one uses with option -d27.
 	 * NOTE: A comment of LZMA SDK source code says this dictionary
 	 * range is from 1 << 12 to 1 << 30. */
@@ -601,9 +584,7 @@ lzip_init(struct archive_read_filter *self)
 		return (ARCHIVE_FATAL);
 	}
 	ret = lzma_raw_decoder(&(state->stream), filters);
-#if LZMA_VERSION < 50010000
 	free(filters[0].options);
-#endif
 	if (ret != LZMA_OK) {
 		set_error(self, ret);
 		return (ARCHIVE_FATAL);
@@ -763,175 +744,6 @@ xz_filter_close(struct archive_read_filter *self)
 
 #else
 
-#if HAVE_LZMADEC_H && HAVE_LIBLZMADEC
-
-/*
- * If we have the older liblzmadec library, then we can handle
- * LZMA streams but not XZ streams.
- */
-
-/*
- * Setup the callbacks.
- */
-static int
-lzma_bidder_init(struct archive_read_filter *self)
-{
-	static const size_t out_block_size = 64 * 1024;
-	void *out_block;
-	struct private_data *state;
-	ssize_t ret, avail_in;
-
-	self->code = ARCHIVE_FILTER_LZMA;
-	self->name = "lzma";
-
-	state = (struct private_data *)calloc(sizeof(*state), 1);
-	out_block = (unsigned char *)malloc(out_block_size);
-	if (state == NULL || out_block == NULL) {
-		archive_set_error(&self->archive->archive, ENOMEM,
-		    "Can't allocate data for lzma decompression");
-		free(out_block);
-		free(state);
-		return (ARCHIVE_FATAL);
-	}
-
-	self->data = state;
-	state->out_block_size = out_block_size;
-	state->out_block = out_block;
-	self->read = lzma_filter_read;
-	self->skip = NULL; /* not supported */
-	self->close = lzma_filter_close;
-
-	/* Prime the lzma library with 18 bytes of input. */
-	state->stream.next_in = (unsigned char *)(uintptr_t)
-	    __archive_read_filter_ahead(self->upstream, 18, &avail_in);
-	if (state->stream.next_in == NULL)
-		return (ARCHIVE_FATAL);
-	state->stream.avail_in = avail_in;
-	state->stream.next_out = state->out_block;
-	state->stream.avail_out = state->out_block_size;
-
-	/* Initialize compression library. */
-	ret = lzmadec_init(&(state->stream));
-	__archive_read_filter_consume(self->upstream,
-	    avail_in - state->stream.avail_in);
-	if (ret == LZMADEC_OK)
-		return (ARCHIVE_OK);
-
-	/* Library setup failed: Clean up. */
-	archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
-	    "Internal error initializing lzma library");
-
-	/* Override the error message if we know what really went wrong. */
-	switch (ret) {
-	case LZMADEC_HEADER_ERROR:
-		archive_set_error(&self->archive->archive,
-		    ARCHIVE_ERRNO_MISC,
-		    "Internal error initializing compression library: "
-		    "invalid header");
-		break;
-	case LZMADEC_MEM_ERROR:
-		archive_set_error(&self->archive->archive, ENOMEM,
-		    "Internal error initializing compression library: "
-		    "out of memory");
-		break;
-	}
-
-	free(state->out_block);
-	free(state);
-	self->data = NULL;
-	return (ARCHIVE_FATAL);
-}
-
-/*
- * Return the next block of decompressed data.
- */
-static ssize_t
-lzma_filter_read(struct archive_read_filter *self, const void **p)
-{
-	struct private_data *state;
-	size_t decompressed;
-	ssize_t avail_in, ret;
-
-	state = (struct private_data *)self->data;
-
-	/* Empty our output buffer. */
-	state->stream.next_out = state->out_block;
-	state->stream.avail_out = state->out_block_size;
-
-	/* Try to fill the output buffer. */
-	while (state->stream.avail_out > 0 && !state->eof) {
-		state->stream.next_in = (unsigned char *)(uintptr_t)
-		    __archive_read_filter_ahead(self->upstream, 1, &avail_in);
-		if (state->stream.next_in == NULL && avail_in < 0) {
-			archive_set_error(&self->archive->archive,
-			    ARCHIVE_ERRNO_MISC,
-			    "truncated lzma input");
-			return (ARCHIVE_FATAL);
-		}
-		state->stream.avail_in = avail_in;
-
-		/* Decompress as much as we can in one pass. */
-		ret = lzmadec_decode(&(state->stream), avail_in == 0);
-		switch (ret) {
-		case LZMADEC_STREAM_END: /* Found end of stream. */
-			state->eof = 1;
-			/* FALL THROUGH */
-		case LZMADEC_OK: /* Decompressor made some progress. */
-			__archive_read_filter_consume(self->upstream,
-			    avail_in - state->stream.avail_in);
-			break;
-		case LZMADEC_BUF_ERROR: /* Insufficient input data? */
-			archive_set_error(&self->archive->archive,
-			    ARCHIVE_ERRNO_MISC,
-			    "Insufficient compressed data");
-			return (ARCHIVE_FATAL);
-		default:
-			/* Return an error. */
-			archive_set_error(&self->archive->archive,
-			    ARCHIVE_ERRNO_MISC,
-			    "Lzma decompression failed");
-			return (ARCHIVE_FATAL);
-		}
-	}
-
-	decompressed = state->stream.next_out - state->out_block;
-	state->total_out += decompressed;
-	if (decompressed == 0)
-		*p = NULL;
-	else
-		*p = state->out_block;
-	return (decompressed);
-}
-
-/*
- * Clean up the decompressor.
- */
-static int
-lzma_filter_close(struct archive_read_filter *self)
-{
-	struct private_data *state;
-	int ret;
-
-	state = (struct private_data *)self->data;
-	ret = ARCHIVE_OK;
-	switch (lzmadec_end(&(state->stream))) {
-	case LZMADEC_OK:
-		break;
-	default:
-		archive_set_error(&(self->archive->archive),
-		    ARCHIVE_ERRNO_MISC,
-		    "Failed to clean up %s compressor",
-		    self->archive->archive.compression_name);
-		ret = ARCHIVE_FATAL;
-	}
-
-	free(state->out_block);
-	free(state);
-	return (ret);
-}
-
-#else
-
 /*
  *
  * If we have no suitable library on this system, we can't actually do
@@ -953,9 +765,6 @@ lzma_bidder_init(struct archive_read_filter *self)
 	return (r);
 }
 
-#endif /* HAVE_LZMADEC_H */
-
-
 static int
 xz_bidder_init(struct archive_read_filter *self)
 {
@@ -984,5 +793,4 @@ lzip_bidder_init(struct archive_read_filter *self)
 	return (r);
 }
 
-
 #endif /* HAVE_LZMA_H */