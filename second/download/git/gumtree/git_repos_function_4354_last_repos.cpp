static void dump_grep_expression_1(struct grep_expr *x, int in)
{
	indent(in);
	switch (x->node) {
	case GREP_NODE_TRUE:
		fprintf(stderr, "true\n");
		break;
	case GREP_NODE_ATOM:
		dump_grep_pat(x->u.atom);
		break;
	case GREP_NODE_NOT:
		fprintf(stderr, "(not\n");
		dump_grep_expression_1(x->u.unary, in+1);
		indent(in);
		fprintf(stderr, ")\n");
		break;
	case GREP_NODE_AND:
		fprintf(stderr, "(and\n");
		dump_grep_expression_1(x->u.binary.left, in+1);
		dump_grep_expression_1(x->u.binary.right, in+1);
		indent(in);
		fprintf(stderr, ")\n");
		break;
	case GREP_NODE_OR:
		fprintf(stderr, "(or\n");
		dump_grep_expression_1(x->u.binary.left, in+1);
		dump_grep_expression_1(x->u.binary.right, in+1);
		indent(in);
		fprintf(stderr, ")\n");
		break;
	}
}