

#ifdef HAVE_ZLIB_H

static int

zip_read_data_deflate(struct archive_read *a, const void **buff,

    size_t *size, int64_t *offset)

{

