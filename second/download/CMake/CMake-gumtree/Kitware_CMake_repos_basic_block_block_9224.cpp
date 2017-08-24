{
				/*
				 * Case 3: our brother is black, our near
				 * nephew is red, and our far nephew is black.
				 * Swap our brother with our near nephew.  
				 * This result in a tree that matches case 4.
				 * (Our father could be red or black).
				 *
				 *	|    F      -->    F      |
				 *	|  x     B  -->  x   B    |
				 *	|      n    -->        n  |
				 */
				__archive_rb_tree_reparent_nodes(brother, which);
				brother = parent->rb_nodes[other];
			}