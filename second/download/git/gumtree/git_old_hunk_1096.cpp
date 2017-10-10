		strbuf_addch(&sb, '\n');
		fprintf(f, "%s", sb.buf);
	}
	strbuf_release(&sb);
}

/* Helper function to display the submodule header line prior to the full
 * summary output. If it can locate the submodule objects directory it will
 * attempt to lookup both the left and right commits and put them into the
 * left and right pointers.
 */
static void show_submodule_header(FILE *f, const char *path,
