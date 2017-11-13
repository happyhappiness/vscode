error("cannot reverse-apply a binary patch "
				     "without the reverse hunk to '%s'",
				     patch->new_name
				     ? patch->new_name : patch->old_name);