static int _remove (avl_tree_t *t, avl_node_t *n)
{
	assert ((t != NULL) && (n != NULL));

	if ((n->left != NULL) && (n->right != NULL))
	{
		avl_node_t *r; /* replacement node */
		if (BALANCE (n) > 0) /* left subtree is higher */
		{
			assert (n->left != NULL);
			r = avl_node_prev (t, n);
			
		}
		else /* right subtree is higher */
		{
			assert (n->right != NULL);
			r = avl_node_next (t, n);
		}

		assert ((r->left == NULL) || (r->right == NULL));

		/* copy content */
		n->key   = r->key;
		n->value = r->value;

		n = r;
	}

	assert ((n->left == NULL) || (n->right == NULL));

	if ((n->left == NULL) && (n->right == NULL))
	{
		/* Deleting a leave is easy */
		if (n->parent == NULL)
		{
			assert (t->root == n);
			t->root = NULL;
		}
		else
		{
			assert ((n->parent->left == n)
					|| (n->parent->right == n));
			if (n->parent->left == n)
				n->parent->left = NULL;
			else
				n->parent->right = NULL;

			rebalance (t, n->parent);
		}

		free_node (n);
	}
	else if (n->left == NULL)
	{
		assert (BALANCE (n) == -1);
		assert ((n->parent == NULL) || (n->parent->left == n) || (n->parent->right == n));
		if (n->parent == NULL)
		{
			assert (t->root == n);
			t->root = n->right;
		}
		else if (n->parent->left == n)
		{
			n->parent->left = n->right;
		}
		else
		{
			n->parent->right = n->right;
		}
		n->right->parent = n->parent;

		if (n->parent != NULL)
			rebalance (t, n->parent);

		n->right = NULL;
		free_node (n);
	}
	else if (n->right == NULL)
	{
		assert (BALANCE (n) == 1);
		assert ((n->parent == NULL) || (n->parent->left == n) || (n->parent->right == n));
		if (n->parent == NULL)
		{
			assert (t->root == n);
			t->root = n->left;
		}
		else if (n->parent->left == n)
		{
			n->parent->left = n->left;
		}
		else
		{
			n->parent->right = n->left;
		}
		n->left->parent = n->parent;

		if (n->parent != NULL)
			rebalance (t, n->parent);

		n->left = NULL;
		free_node (n);
	}
	else
	{
		assert (0);
	}

	return (0);
}