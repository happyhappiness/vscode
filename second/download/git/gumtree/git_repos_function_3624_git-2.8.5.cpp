static struct grep_expr *grep_or_expr(struct grep_expr *left, struct grep_expr *right)
{
	struct grep_expr *z = xcalloc(1, sizeof(*z));
	z->node = GREP_NODE_OR;
	z->u.binary.left = left;
	z->u.binary.right = right;
	return z;
}