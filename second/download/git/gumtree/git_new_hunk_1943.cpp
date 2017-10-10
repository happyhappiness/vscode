	struct menu_item *menu_item;
	struct string_list_item *string_list_item;
	int i;

	switch (stuff->type) {
	default:
		die("Bad type of menu_stuff when print menu");
	case MENU_STUFF_TYPE_MENU_ITEM:
		menu_item = (struct menu_item *)stuff->stuff;
		for (i = 0; i < stuff->nr; i++, menu_item++) {
			const char *p;
			int highlighted = 0;

