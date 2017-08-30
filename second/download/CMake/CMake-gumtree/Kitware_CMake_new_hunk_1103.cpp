		/* disk_start = archive_le16dec(p + 34); */ /* Better be zero. */

		/* internal_attributes = archive_le16dec(p + 36); */ /* text bit */

		external_attributes = archive_le32dec(p + 38);

		zip_entry->local_header_offset =

		    archive_le32dec(p + 42) + correction;



		/* If we can't guess the mode, leave it zero here;

		   when we read the local file header we might get

		   more information. */

		zip_entry->mode = 0;

		if (zip_entry->system == 3) {

			zip_entry->mode = external_attributes >> 16;

		}



		/*

		 * Mac resource fork files are stored under the

		 * "__MACOSX/" directory, so we should check if

		 * it is.

		 */

		/* Make sure we have the file name. */

		if ((p = __archive_read_ahead(a, 46 + filename_length, NULL))

		    == NULL)

			return ARCHIVE_FATAL;

		name = p + 46;

		r = rsrc_basename(name, filename_length);

		if (filename_length >= 9 &&

		    strncmp("__MACOSX/", name, 9) == 0) {

			/* If this file is not a resource fork nor

			 * a directory. We should treat it as a non

			 * resource fork file to expose it. */

			if (name[filename_length-1] != '/' &&

			    (r - name < 3 || r[0] != '.' || r[1] != '_')) {

				__archive_rb_tree_insert_node(&zip->tree,

				    &zip_entry->node);

				/* Expose its parent directories. */

				expose_parent_dirs(zip, name, filename_length);

			} else {

				/* This file is a resource fork file or

				 * a directory. */

				archive_strncpy(&(zip_entry->rsrcname), name,

				    filename_length);

				__archive_rb_tree_insert_node(&zip->tree_rsrc,

				    &zip_entry->node);

			}

		} else {

			/* Generate resource fork name to find its resource

			 * file at zip->tree_rsrc. */

			archive_strcpy(&(zip_entry->rsrcname), "__MACOSX/");

			archive_strncat(&(zip_entry->rsrcname), name, r - name);

			archive_strcat(&(zip_entry->rsrcname), "._");

			archive_strncat(&(zip_entry->rsrcname),

			    name + (r - name), filename_length - (r - name));

			/* Register an entry to RB tree to sort it by

			 * file offset. */

			__archive_rb_tree_insert_node(&zip->tree,

			    &zip_entry->node);

		}



		/* We don't read the filename until we get to the

		   local file header.  Reading it here would speed up

		   table-of-contents operations (removing the need to

		   find and read local file header to get the

		   filename) at the cost of requiring a lot of extra

		   space. */

		/* We don't read the extra block here.  We assume it

		   will be duplicated at the local file header. */

		__archive_read_consume(a,

		    46 + filename_length + extra_length + comment_length);

	}



	return ARCHIVE_OK;

}



static int64_t

zip_read_consume(struct archive_read *a, int64_t bytes)

{

	struct zip *zip = (struct zip *)a->format->data;

	int64_t skip;



	skip = __archive_read_consume(a, bytes);

	if (skip > 0)

		zip->offset += skip;

	return (skip);

}



static int

zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,

    struct zip_entry *rsrc)

{

	struct zip *zip = (struct zip *)a->format->data;

	unsigned char *metadata, *mp;

	int64_t offset = zip->offset;

	size_t remaining_bytes, metadata_bytes;

	ssize_t hsize;

	int ret = ARCHIVE_OK, eof;



	switch(rsrc->compression) {

	case 0:  /* No compression. */

#ifdef HAVE_ZLIB_H

	case 8: /* Deflate compression. */

#endif

		break;

	default: /* Unsupported compression. */

		/* Return a warning. */

		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

		    "Unsupported ZIP compression method (%s)",

		    compression_name(rsrc->compression));

		/* We can't decompress this entry, but we will

		 * be able to skip() it and try the next entry. */

		return (ARCHIVE_WARN);

	}



	if (rsrc->uncompressed_size > (128 * 1024)) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

		    "Mac metadata is too large: %jd > 128K bytes",

		    (intmax_t)rsrc->uncompressed_size);

		return (ARCHIVE_WARN);

	}



	metadata = malloc((size_t)rsrc->uncompressed_size);

	if (metadata == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate memory for Mac metadata");

		return (ARCHIVE_FATAL);

	}



	if (zip->offset < rsrc->local_header_offset)

		zip_read_consume(a, rsrc->local_header_offset - zip->offset);

	else if (zip->offset != rsrc->local_header_offset) {

		__archive_read_seek(a, rsrc->local_header_offset, SEEK_SET);

		zip->offset = zip->entry->local_header_offset;

	}



	hsize = zip_get_local_file_header_size(a, 0);

	zip_read_consume(a, hsize);



	remaining_bytes = (size_t)rsrc->compressed_size;

	metadata_bytes = (size_t)rsrc->uncompressed_size;

	mp = metadata;

	eof = 0;

	while (!eof && remaining_bytes) {

		const unsigned char *p;

		ssize_t bytes_avail;

		size_t bytes_used;



		p = __archive_read_ahead(a, 1, &bytes_avail);

		if (p == NULL) {

			archive_set_error(&a->archive,

			    ARCHIVE_ERRNO_FILE_FORMAT,

			    "Truncated ZIP file header");

			ret = ARCHIVE_WARN;

			goto exit_mac_metadata;

		}

		if ((size_t)bytes_avail > remaining_bytes)

			bytes_avail = remaining_bytes;

		switch(rsrc->compression) {

		case 0:  /* No compression. */

			memcpy(mp, p, bytes_avail);

			bytes_used = (size_t)bytes_avail;

			metadata_bytes -= bytes_used;

			mp += bytes_used;

			if (metadata_bytes == 0)

				eof = 1;

			break;

#ifdef HAVE_ZLIB_H

		case 8: /* Deflate compression. */

		{

			int r;



			ret = zip_deflate_init(a, zip);

			if (ret != ARCHIVE_OK)

				goto exit_mac_metadata;

			zip->stream.next_in =

			    (Bytef *)(uintptr_t)(const void *)p;

			zip->stream.avail_in = (uInt)bytes_avail;

			zip->stream.total_in = 0;

			zip->stream.next_out = mp;

			zip->stream.avail_out = (uInt)metadata_bytes;

			zip->stream.total_out = 0;



			r = inflate(&zip->stream, 0);

			switch (r) {

			case Z_OK:

				break;

			case Z_STREAM_END:

				eof = 1;

				break;

			case Z_MEM_ERROR:

				archive_set_error(&a->archive, ENOMEM,

				    "Out of memory for ZIP decompression");

				ret = ARCHIVE_FATAL;

				goto exit_mac_metadata;

			default:

				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "ZIP decompression failed (%d)", r);

				ret = ARCHIVE_FATAL;

				goto exit_mac_metadata;

			}

			bytes_used = zip->stream.total_in;

			metadata_bytes -= zip->stream.total_out;

			mp += zip->stream.total_out;

			break;

		}

#endif

		default:

			bytes_used = 0;

			break;

		}

		zip_read_consume(a, bytes_used);

		remaining_bytes -= bytes_used;

	}

	archive_entry_copy_mac_metadata(entry, metadata,

	    (size_t)rsrc->uncompressed_size - metadata_bytes);



	__archive_read_seek(a, offset, SEEK_SET);

	zip->offset = offset;

exit_mac_metadata:

	zip->decompress_init = 0;

	free(metadata);

	return (ret);

}



static int

archive_read_format_zip_seekable_read_header(struct archive_read *a,

	struct archive_entry *entry)

{

	struct zip *zip = (struct zip *)a->format->data;

	struct zip_entry *rsrc;

	int r, ret = ARCHIVE_OK;



	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;

	if (a->archive.archive_format_name == NULL)

