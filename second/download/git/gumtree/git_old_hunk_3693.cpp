			char *fname;
			fname = mkpathdup("%s/old-%s%s",
					  packdir,
					  item->string,
					  exts[ext].name);
			if (remove_path(fname))
				warning(_("removing '%s' failed"), fname);
			free(fname);
		}
	}

	/* End of pack replacement. */

