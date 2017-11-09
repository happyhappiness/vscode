static struct grep_expr *grep_splice_or(struct grep_expr *x, struct grep_expr *y)
{
	struct grep_expr *z = x;

	while (x) {
		assert(x->node == GREP_NODE_OR);
		if (x->u.binary.right &&
		    x->u.binary.right->node == GREP_NODE_TRUE) {
			x->u.binary.right = y;
			break;
		}
		x = x->u.binary.right;
	}
	return z;
}