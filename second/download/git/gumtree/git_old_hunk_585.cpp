
		it = &(s->ignored.items[i]);
		wt_shortstatus_other(it, s, "!!");
	}
}

void wt_porcelain_print(struct wt_status *s)
{
	s->use_color = 0;
	s->relative_paths = 0;
	s->prefix = NULL;
	s->no_gettext = 1;
	wt_shortstatus_print(s);
}
