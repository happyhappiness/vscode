static void remove_first_line(struct image *img)
{
	img->buf += img->line[0].len;
	img->len -= img->line[0].len;
	img->line++;
	img->nr--;
}