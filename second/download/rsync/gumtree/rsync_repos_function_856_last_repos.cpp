void get_md5(uchar *out, const uchar *input, int n)
{
	md_context ctx;
	md5_begin(&ctx);
	md5_update(&ctx, input, n);
	md5_result(&ctx, out);
}