(me->parentdir.s)
				archive_string_sprintf(&mtree->buf,
				    "# %s/%s\n",
				    me->parentdir.s, me->basename.s);
			else
				archive_string_sprintf(&mtree->buf,
				    "# %s\n",
				    me->basename.s)