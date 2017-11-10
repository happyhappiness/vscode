static void free_pattern_expr(struct grep_expr *x)
{
	switch (x->node) {
	case GREP_NODE_TRUE:
	case GREP_NODE_ATOM:
		break;
	case GREP_NODE_NOT:
		free_pattern_expr(x->u.unary);
		break;
	case GREP_NODE_AND:
	case GREP_NODE_OR:
		free_pattern_expr(x->u.binary.left);
		free_pattern_expr(x->u.binary.right);
		break;
	}
	free(x);
}