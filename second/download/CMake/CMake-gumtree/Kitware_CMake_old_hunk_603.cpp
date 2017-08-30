	 * other libarchive code that assumes a successful forward
	 * seek means it can also seek backwards.
	 */
	if (self->archive->client.seeker == NULL)
		return (ARCHIVE_FAILED);
	return (self->archive->client.seeker)(&self->archive->archive,
	    self->data, offset, whence);
}
