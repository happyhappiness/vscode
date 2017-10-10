
			if (safe_create_leading_directories_const(filename)) {
				error("Could not create lost-found");
				free(filename);
				return;
			}
			f = xfopen(filename, "w");
			if (obj->type == OBJ_BLOB) {
				if (stream_blob_to_fd(fileno(f), &obj->oid, NULL, 1))
					die_errno("Could not write '%s'", filename);
			} else
				fprintf(f, "%s\n", describe_object(obj));
			if (fclose(f))
