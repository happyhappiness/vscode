		}
		if (!is_bare && is_from_line(buf.buf, buf.len))
			break; /* done with one message */
	}
	fclose(output);
	return status;

 corrupt:
	if (output)
		fclose(output);
	unlink(name);
	fprintf(stderr, "corrupt mailbox\n");
	exit(1);
}

static int populate_maildir_list(struct string_list *list, const char *path)
{
	DIR *dir;
	struct dirent *dent;
