		 * file was not renamed.
		 */
		int ostage1 = o->branch1 == branch1 ? 3 : 2;
		int ostage2 = ostage1 ^ 1;

		ci->ren1_other.path = pair1->one->path;
		oidcpy(&ci->ren1_other.oid, &src_entry1->stages[ostage1].oid);
		ci->ren1_other.mode = src_entry1->stages[ostage1].mode;

		ci->ren2_other.path = pair2->one->path;
		oidcpy(&ci->ren2_other.oid, &src_entry2->stages[ostage2].oid);
		ci->ren2_other.mode = src_entry2->stages[ostage2].mode;
	}
}

static int show(struct merge_options *o, int v)
{
	return (!o->call_depth && o->verbosity >= v) || o->verbosity >= 5;
}

__attribute__((format (printf, 3, 4)))
static void output(struct merge_options *o, int v, const char *fmt, ...)
{
	va_list ap;

	if (!show(o, v))
