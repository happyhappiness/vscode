endif /* _PC_NAME_MAX */
		/*
		 * Some systems (HP-UX or others?) incorrectly defined
		 * NAME_MAX macro to be a smaller value.
		 */
#  if defined(NAME_MAX) && NAME_MAX >= 255
		t->current_filesystem->name_max = NAME_MAX