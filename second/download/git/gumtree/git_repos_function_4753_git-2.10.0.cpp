static void remove_last_line(struct image *img)
{
	img->len -= img->line[--img->nr].len;
}