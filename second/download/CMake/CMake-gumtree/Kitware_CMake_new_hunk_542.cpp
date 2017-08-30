

		if (bytes_read == -1) {

			archive_set_error(f->archive, errno,

			    "Error reading from program: %s", data->program_name);

			ret = ARCHIVE_FATAL;

			goto cleanup;

		}

