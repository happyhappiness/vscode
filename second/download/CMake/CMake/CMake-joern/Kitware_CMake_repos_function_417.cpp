static int
compression_unsupported_encoder(struct archive *a,
    struct la_zstream *lastrm, const char *name)
{

	archive_set_error(a, ARCHIVE_ERRNO_MISC,
	    "%s compression not supported on this platform", name);
	lastrm->valid = 0;
	lastrm->real_stream = NULL;
	return (ARCHIVE_FAILED);
}