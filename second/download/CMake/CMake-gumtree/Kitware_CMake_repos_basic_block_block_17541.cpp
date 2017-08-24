{
			struct file *vp;
			struct archive_string as;

			archive_string_init(&as);
			archive_strncat(&as, p, fn - p + l);
			if (as.s[as.length-1] == '/') {
				as.s[as.length-1] = '\0';
				as.length--;
			}
			vp = file_create_virtual_dir(a, xar, as.s);
			if (vp == NULL) {
				archive_string_free(&as);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}
			archive_string_free(&as);
			if (file_gen_utility_names(a, vp) <= ARCHIVE_FAILED)
				return (ARCHIVE_FATAL);
			file_add_child_tail(dent, vp);
			file_register(xar, vp);
			np = vp;

			fn += l;
			if (fn[0] == '/')
				fn++;
			l = get_path_component(name, sizeof(name), fn);
			if (l < 0) {
				archive_string_free(&as);
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "A name buffer is too small");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}
			dent = np;
		}