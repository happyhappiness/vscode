static void add_line_info(struct image *img, const char *bol, size_t len, unsigned flag)
{
	ALLOC_GROW(img->line_allocated, img->nr + 1, img->alloc);
	img->line_allocated[img->nr].len = len;
	img->line_allocated[img->nr].hash = hash_line(bol, len);
	img->line_allocated[img->nr].flag = flag;
	img->nr++;
}