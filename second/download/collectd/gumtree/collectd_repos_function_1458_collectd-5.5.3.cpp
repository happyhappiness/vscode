static int riemann_event_add_tag (Event *event, char const *tag) /* {{{ */
{
	return (strarray_add (&event->tags, &event->n_tags, tag));
}