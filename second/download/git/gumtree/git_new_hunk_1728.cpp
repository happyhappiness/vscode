		}
		if (!is_bare && is_from_line(buf.buf, buf.len))
			break; /* done with one message */
	}
	fclose(output);
	return status;
}

static int populate_maildir_list(struct string_list *list, const char *path)
{
	DIR *dir;
	struct dirent *dent;
