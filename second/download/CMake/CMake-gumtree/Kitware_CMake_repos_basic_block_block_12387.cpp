{
	if (_a && _a->format) {
		struct rar * rar = (struct rar *)_a->format->data;
		if (rar) {
			return rar->has_encrypted_entries;
		}
	}
	return ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
}