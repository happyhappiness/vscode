		free(a);
	}
	free(e->attrs);
	free(e);
}

static const char *builtin_attr[] = {
	"[attr]binary -diff -merge -text",
	NULL,
};

static void handle_attr_line(struct attr_stack *res,
