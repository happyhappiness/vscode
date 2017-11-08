int free_chmod_mode(struct chmod_mode_struct *chmod_modes)
{
	struct chmod_mode_struct *next;

	while (chmod_modes) {
		next = chmod_modes->next;
		free(chmod_modes);
		chmod_modes = next;
	}
	return 0;
}