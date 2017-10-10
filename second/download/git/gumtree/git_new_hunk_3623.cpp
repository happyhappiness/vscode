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
