{
			/* stat(2) st_dev field, e.g. the device ID where the
			 * inode resides */
			int r;
			dev_t dev;

			r = parse_device(&dev, &a->archive, val);
			if (r == ARCHIVE_OK)
				archive_entry_set_dev(entry, dev);
			return r;
		}