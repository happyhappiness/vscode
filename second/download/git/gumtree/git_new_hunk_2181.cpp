	stop_progress(&tdata.prg);

	if (bitmap_equals(result, tdata.base))
		fprintf(stderr, "OK!\n");
	else
		fprintf(stderr, "Mismatch!\n");

	free(result);
}

static int rebuild_bitmap(uint32_t *reposition,
			  struct ewah_bitmap *source,
			  struct bitmap *dest)
{
