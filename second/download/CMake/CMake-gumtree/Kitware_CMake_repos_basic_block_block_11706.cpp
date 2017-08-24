(parent != NULL && (flags & 0x02) &&
		    (parent->re || parent->re_descendant))
			file->re_descendant = 1