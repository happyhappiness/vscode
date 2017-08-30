static int
archive_read_format_lha_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	struct lha *lha = (struct lha *)(a->format->data);
	int r;

	if (lha->entry_unconsumed) {
		/* Consume as much as the decompressor actually used. */
		__archive_read_consume(a, lha->entry_unconsumed);
		lha->entry_unconsumed = 0;
	}
	if (lha->end_of_entry) {
		if (!lha->end_of_entry_cleanup) {
			if ((lha->setflag & CRC_IS_SET) &&
			    lha->crc != lha->entry_crc_calculated) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "LHa data CRC error");
				return (ARCHIVE_WARN);
			}

			/* End-of-entry cleanup done. */
			lha->end_of_entry_cleanup = 1;
		}
		*offset = lha->entry_offset;
		*size = 0;
		*buff = NULL;
		return (ARCHIVE_EOF);
	}

	if (lha->entry_is_compressed)
		r =  lha_read_data_lzh(a, buff, size, offset);
	else
		/* No compression. */
		r =  lha_read_data_none(a, buff, size, offset);
	return (r);
}