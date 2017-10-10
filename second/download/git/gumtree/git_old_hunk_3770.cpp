		 * file was not renamed.
		 */
		int ostage1 = o->branch1 == branch1 ? 3 : 2;
		int ostage2 = ostage1 ^ 1;

		ci->ren1_other.path = pair1->one->path;
		hashcpy(ci->ren1_other.sha1, src_entry1->stages[ostage1].sha);
		ci->ren1_other.mode = src_entry1->stages[ostage1].mode;

		ci->ren2_other.path = pair2->one->path;
		hashcpy(ci->ren2_other.sha1, src_entry2->stages[ostage2].sha);
		ci->ren2_other.mode = src_entry2->stages[ostage2].mode;
	}
}

static int show(struct merge_options *o, int v)
{
	return (!o->call_depth && o->verbosity >= v) || o->verbosity >= 5;
}

static void flush_output(struct merge_options *o)
{
	if (o->obuf.len) {
		fputs(o->obuf.buf, stdout);
		strbuf_reset(&o->obuf);
	}
}

__attribute__((format (printf, 3, 4)))
static void output(struct merge_options *o, int v, const char *fmt, ...)
{
	va_list ap;

	if (!show(o, v))
