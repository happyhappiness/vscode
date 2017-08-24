(iso9660->opt.boot) {
		/* Find out the boot file entry. */
		ret = isoent_find_out_boot_file(a, iso9660->primary.rootent);
		if (ret < 0)
			return (ret);
		/* Reconvert the boot file from zisofs'ed form to
		 * plain form. */
		ret = zisofs_rewind_boot_file(a);
		if (ret < 0)
			return (ret);
		/* Write remaining data out to the temporary file. */
		if (wb_remaining(a) > 0) {
			ret = wb_write_out(a);
			if (ret < 0)
				return (ret);
		}
		/* Create the boot catalog. */
		ret = isoent_create_boot_catalog(a, iso9660->primary.rootent);
		if (ret < 0)
			return (ret);
	}