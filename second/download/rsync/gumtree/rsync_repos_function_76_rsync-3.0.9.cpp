int tweak_mode(int mode, struct chmod_mode_struct *chmod_modes)
{
	int IsX = mode & 0111;
	int NonPerm = mode & ~CHMOD_BITS;

	for ( ; chmod_modes; chmod_modes = chmod_modes->next) {
		if ((chmod_modes->flags & FLAG_DIRS_ONLY) && !S_ISDIR(NonPerm))
			continue;
		if ((chmod_modes->flags & FLAG_FILES_ONLY) && S_ISDIR(NonPerm))
			continue;
		mode &= chmod_modes->ModeAND;
		if ((chmod_modes->flags & FLAG_X_KEEP) && !IsX && !S_ISDIR(NonPerm))
			mode |= chmod_modes->ModeOR & ~0111;
		else
			mode |= chmod_modes->ModeOR;
	}

	return mode | NonPerm;
}