{
			*p = L'\0';
			tree_append(t, base, p - base);
			t->dirname_length = archive_strlen(&t->path);
			base = p + 1;
		}