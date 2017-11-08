void fill_filespec(struct diff_filespec *spec, const struct object_id *oid,
		   int oid_valid, unsigned short mode)
{
	if (mode) {
		spec->mode = canon_mode(mode);
		oidcpy(&spec->oid, oid);
		spec->oid_valid = oid_valid;
	}
}