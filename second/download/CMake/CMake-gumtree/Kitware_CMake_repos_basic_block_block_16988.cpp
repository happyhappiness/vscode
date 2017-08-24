{
			/* Find largest suffix that will fit. */
			/* Note: strlen() > 100, so strlen() - 100 - 1 >= 0 */
			suffix = strchr(path + path_length - 100 - 1, '/');
			/* Don't attempt an empty prefix. */
			if (suffix == path)
				suffix = strchr(suffix + 1, '/');
			/* We can put it in the ustar header if it's
			 * all ASCII and it's either <= 100 characters
			 * or can be split at a '/' into a prefix <=
			 * 155 chars and a suffix <= 100 chars.  (Note
			 * the strchr() above will return NULL exactly
			 * when the path can't be split.)
			 */
			if (suffix == NULL       /* Suffix > 100 chars. */
			    || suffix[1] == '\0'    /* empty suffix */
			    || suffix - path > 155)  /* Prefix > 155 chars */
			{
				add_pax_attr(&(pax->pax_header), "path", path);
				archive_entry_set_pathname(entry_main,
				    build_ustar_entry_name(ustar_entry_name,
					path, path_length, NULL));
				need_extension = 1;
			}
		}