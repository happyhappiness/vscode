{
			/* Copy prefix and remainder to appropriate places */
			memcpy(h + USTAR_prefix_offset, pp, p - pp);
			memcpy(h + USTAR_name_offset, p + 1,
			    pp + copy_length - p - 1);
		}