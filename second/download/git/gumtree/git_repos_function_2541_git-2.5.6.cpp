static void move_diff_queue(struct diff_queue_struct *dst,
			    struct diff_queue_struct *src)
{
	assert(src != dst);
	memcpy(dst, src, sizeof(struct diff_queue_struct));
	DIFF_QUEUE_CLEAR(src);
}