output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
			       "and %s in %s. Version %s of %s left in tree at %s."),
			       change, path, o->branch1, change_past,
			       o->branch2, o->branch2, path, renamed);