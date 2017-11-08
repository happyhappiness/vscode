static inline unsigned int ce_mode_from_stat(const struct cache_entry *ce,
					     unsigned int mode)
{
	extern int trust_executable_bit, has_symlinks;
	if (!has_symlinks && S_ISREG(mode) &&
	    ce && S_ISLNK(ce->ce_mode))
		return ce->ce_mode;
	if (!trust_executable_bit && S_ISREG(mode)) {
		if (ce && S_ISREG(ce->ce_mode))
			return ce->ce_mode;
		return create_ce_mode(0666);
	}
	return create_ce_mode(mode);
}