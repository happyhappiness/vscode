(r >= 0) {
		/*
		 * Ouch.  Clearing the buffer like this hurts, especially
		 * at bid time.  A lot of our efficiency at bid time comes
		 * from having bidders reuse the data we've already read.
		 *
		 * TODO: If the seek request is in data we already
		 * have, then don't call the seek callback.
		 *
		 * TODO: Zip seeks to end-of-file at bid time.  If
		 * other formats also start doing this, we may need to
		 * find a way for clients to fudge the seek offset to
		 * a block boundary.
		 *
		 * Hmmm... If whence was SEEK_END, we know the file
		 * size is (r - offset).  Can we use that to simplify
		 * the TODO items above?
		 */
		filter->avail = filter->client_avail = 0;
		filter->next = filter->buffer;
		filter->position = r;
		filter->end_of_file = 0;
	}