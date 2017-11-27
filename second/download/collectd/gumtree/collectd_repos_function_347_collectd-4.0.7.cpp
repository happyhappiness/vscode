static void rebalance (avl_tree_t *t, avl_node_t *n)
{
	int b_top;
	int b_bottom;

	while (n != NULL)
	{
		b_top = BALANCE (n);
		assert ((b_top >= -2) && (b_top <= 2));

		if (b_top == -2)
		{
			assert (n->right != NULL);
			b_bottom = BALANCE (n->right);
			assert ((b_bottom >= -1) || (b_bottom <= 1));
			if (b_bottom == 1)
				n = rotate_right_left (t, n);
			else
				n = rotate_left (t, n);
		}
		else if (b_top == 2)
		{
			assert (n->left != NULL);
			b_bottom = BALANCE (n->left);
			assert ((b_bottom >= -1) || (b_bottom <= 1));
			if (b_bottom == -1)
				n = rotate_left_right (t, n);
			else
				n = rotate_right (t, n);
		}
		else
		{
			int height = calc_height (n);
			if (height == n->height)
				break;
			n->height = height;
		}

		assert (n->height == calc_height (n));

		n = n->parent;
	} /* while (n != NULL) */
}