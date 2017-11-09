static inline void setup_rename_conflict_info(enum rename_type rename_type,
					      struct diff_filepair *pair1,
					      struct diff_filepair *pair2,
					      const char *branch1,
					      const char *branch2,
					      struct stage_data *dst_entry1,
					      struct stage_data *dst_entry2,
					      struct merge_options *o,
					      struct stage_data *src_entry1,
					      struct stage_data *src_entry2)
{
	struct rename_conflict_info *ci = xcalloc(1, sizeof(struct rename_conflict_info));
	ci->rename_type = rename_type;
	ci->pair1 = pair1;
	ci->branch1 = branch1;
	ci->branch2 = branch2;

	ci->dst_entry1 = dst_entry1;
	dst_entry1->rename_conflict_info = ci;
	dst_entry1->processed = 0;

	assert(!pair2 == !dst_entry2);
	if (dst_entry2) {
		ci->dst_entry2 = dst_entry2;
		ci->pair2 = pair2;
		dst_entry2->rename_conflict_info = ci;
	}

	if (rename_type == RENAME_TWO_FILES_TO_ONE) {
		/*
		 * For each rename, there could have been
		 * modifications on the side of history where that
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