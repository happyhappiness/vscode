		dump_marks_helper(rpt, 0, marks);

	fputc('\n', rpt);
	fputs("-------------------\n", rpt);
	fputs("END OF CRASH REPORT\n", rpt);
	fclose(rpt);
	free(loc);
}

static void end_packfile(void);
static void unkeep_all_packs(void);
static void dump_marks(void);

