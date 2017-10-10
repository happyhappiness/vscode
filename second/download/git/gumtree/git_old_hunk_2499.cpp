		default:
			die("BUG: unknown get_sha1_with_context result %d\n",
			       result);
			break;
		}
		fflush(stdout);
		return 0;
	}

	if (ctx.mode == 0) {
		printf("symlink %"PRIuMAX"\n%s\n",
		       (uintmax_t)ctx.symlink_path.len,
		       ctx.symlink_path.buf);
		fflush(stdout);
		return 0;
	}

	if (sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
		printf("%s missing\n", obj_name);
		fflush(stdout);
		return 0;
	}

	strbuf_expand(&buf, opt->format, expand_format, data);
	strbuf_addch(&buf, '\n');
	write_or_die(1, buf.buf, buf.len);
	strbuf_release(&buf);

	if (opt->print_contents) {
		print_object_or_die(1, data);
		write_or_die(1, "\n", 1);
	}
	return 0;
}

static int batch_objects(struct batch_options *opt)
{
	struct strbuf buf = STRBUF_INIT;
