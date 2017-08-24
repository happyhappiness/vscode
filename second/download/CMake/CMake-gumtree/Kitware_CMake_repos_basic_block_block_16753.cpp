{
			/*
			 * Descend the tree.
			 */
			np = np->dir_info->children.first;
			if (mtree->indent)
				mtree->depth++;
			continue;
		}