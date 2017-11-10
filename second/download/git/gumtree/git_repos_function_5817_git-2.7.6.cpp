static void check_preimage_overflow(off_t a, off_t b)
{
	if (signed_add_overflows(a, b))
		die("blob too large for current definition of off_t");
}