strbuf_addf(&o->obuf, "%s ",
			find_unique_abbrev(commit->object.oid.hash,
				DEFAULT_ABBREV));