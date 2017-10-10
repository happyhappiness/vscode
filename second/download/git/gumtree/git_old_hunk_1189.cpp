						     state->p_value, state->linenr);
					return -128;
				}
				patch->old_name = xstrdup(patch->def_name);
				patch->new_name = xstrdup(patch->def_name);
			}
			if (!patch->is_delete && !patch->new_name) {
				error(_("git diff header lacks filename information "
					     "(line %d)"), state->linenr);
				return -128;
			}
			patch->is_toplevel_relative = 1;
			*hdrsize = git_hdr_len;
