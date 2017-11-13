static void show_filemodify(struct diff_queue_struct *q,
			    struct diff_options *options, void *data)
{
	int i;

	/*
	 * Handle files below a directory first, in case they are all deleted
	 * and the directory changes to a file or symlink.
	 */
	QSORT(q->queue, q->nr, depth_first);

	for (i = 0; i < q->nr; i++) {
		struct diff_filespec *ospec = q->queue[i]->one;
		struct diff_filespec *spec = q->queue[i]->two;

		switch (q->queue[i]->status) {
		case DIFF_STATUS_DELETED:
			printf("D ");
			print_path(spec->path);
			putchar('\n');
			break;

		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			printf("%c ", q->queue[i]->status);
			print_path(ospec->path);
			putchar(' ');
			print_path(spec->path);
			putchar('\n');

			if (!oidcmp(&ospec->oid, &spec->oid) &&
			    ospec->mode == spec->mode)
				break;
			/* fallthrough */

		case DIFF_STATUS_TYPE_CHANGED:
		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_ADDED:
			/*
			 * Links refer to objects in another repositories;
			 * output the SHA-1 verbatim.
			 */
			if (no_data || S_ISGITLINK(spec->mode))
				printf("M %06o %s ", spec->mode,
				       sha1_to_hex(anonymize ?
						   anonymize_sha1(spec->oid.hash) :
						   spec->oid.hash));
			else {
				struct object *object = lookup_object(spec->oid.hash);
				printf("M %06o :%d ", spec->mode,
				       get_object_mark(object));
			}
			print_path(spec->path);
			putchar('\n');
			break;

		default:
			die("Unexpected comparison status '%c' for %s, %s",
				q->queue[i]->status,
				ospec->path ? ospec->path : "none",
				spec->path ? spec->path : "none");
		}
	}
}