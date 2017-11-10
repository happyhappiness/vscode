static void add_descendants_to_write_order(struct object_entry **wo,
					   unsigned int *endp,
					   struct object_entry *e)
{
	int add_to_order = 1;
	while (e) {
		if (add_to_order) {
			struct object_entry *s;
			/* add this node... */
			add_to_write_order(wo, endp, e);
			/* all its siblings... */
			for (s = e->delta_sibling; s; s = s->delta_sibling) {
				add_to_write_order(wo, endp, s);
			}
		}
		/* drop down a level to add left subtree nodes if possible */
		if (e->delta_child) {
			add_to_order = 1;
			e = e->delta_child;
		} else {
			add_to_order = 0;
			/* our sibling might have some children, it is next */
			if (e->delta_sibling) {
				e = e->delta_sibling;
				continue;
			}
			/* go back to our parent node */
			e = e->delta;
			while (e && !e->delta_sibling) {
				/* we're on the right side of a subtree, keep
				 * going up until we can go right again */
				e = e->delta;
			}
			if (!e) {
				/* done- we hit our original root node */
				return;
			}
			/* pass it off to sibling at this level */
			e = e->delta_sibling;
		}
	};
}