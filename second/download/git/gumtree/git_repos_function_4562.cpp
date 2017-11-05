static void clear_image(struct image *image)
{
	free(image->buf);
	free(image->line_allocated);
	memset(image, 0, sizeof(*image));
}