{
		/* If the client provided a seeker but not a skipper,
		 * we can use the seeker to skip forward.
		 *
		 * Note: This isn't always a good idea.  The client
		 * skipper is allowed to skip by less than requested
		 * if it needs to maintain block alignment.  The
		 * seeker is not allowed to play such games, so using
		 * the seeker here may be a performance loss compared
		 * to just reading and discarding.  That's why we
		 * only do this for skips of over 64k.
		 */
		int64_t before = self->position;
		int64_t after = (self->archive->client.seeker)
		    (&self->archive->archive, self->data, request, SEEK_CUR);
		if (after != before + request)
			return ARCHIVE_FATAL;
		return after - before;
	}