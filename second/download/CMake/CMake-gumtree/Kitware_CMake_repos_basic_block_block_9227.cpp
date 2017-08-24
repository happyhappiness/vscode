(RB_RED_P(parent)
		    && RB_BLACK_P(brother)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {
			/*
			 * We are black, our father is red, our brother and
			 * both nephews are black.  Simply invert/exchange the
			 * colors of our father and brother (to black and red
			 * respectively).
			 *
			 *	|    f        -->    F        |
			 *	|  *     B    -->  *     b    |
			 *	|      N   N  -->      N   N  |
			 */
			RB_MARK_BLACK(parent);
			RB_MARK_RED(brother);
			break;		/* We're done! */
		} else {
			/*
			 * Our brother must be black and have at least one
			 * red child (it may have two).
			 */
			if (RB_BLACK_P(brother->rb_nodes[other])) {
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
			/*
			 * Case 4: our brother is black and our far nephew
			 * is red.  Swap our father and brother locations and
			 * change our far nephew to black.  (these can be
			 * done in either order so we change the color first).
			 * The result is a valid red-black tree and is a
			 * terminal case.  (again we don't care about the
			 * father's color)
			 *
			 * If the father is red, we will get a red-black-black
			 * tree:
			 *	|  f      ->  f      -->    b    |
			 *	|    B    ->    B    -->  F   N  |
			 *	|      n  ->      N  -->         |
			 *
			 * If the father is black, we will get an all black
			 * tree:
			 *	|  F      ->  F      -->    B    |
			 *	|    B    ->    B    -->  F   N  |
			 *	|      n  ->      N  -->         |
			 *
			 * If we had two red nephews, then after the swap,
			 * our former father would have a red grandson. 
			 */
			if (brother->rb_nodes[other] == NULL)
				return;/* The tree may be broken. */
			RB_MARK_BLACK(brother->rb_nodes[other]);
			__archive_rb_tree_reparent_nodes(parent, other);
			break;		/* We're done! */
		}