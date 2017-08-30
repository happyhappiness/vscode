	 */

	if (location > 0 &&

	    (location + ((fsize + iso9660->logical_block_size -1)

	       / iso9660->logical_block_size))

			> (uint32_t)iso9660->volume_block) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Invalid location of extent of file");

		return (NULL);

