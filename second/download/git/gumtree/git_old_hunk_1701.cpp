			/*
			 * Links refer to objects in another repositories;
			 * output the SHA-1 verbatim.
			 */
			if (no_data || S_ISGITLINK(spec->mode))
				printf("M %06o %s ", spec->mode,
				       sha1_to_hex(spec->sha1));
			else {
				struct object *object = lookup_object(spec->sha1);
				printf("M %06o :%d ", spec->mode,
				       get_object_mark(object));
			}
			print_path(spec->path);
