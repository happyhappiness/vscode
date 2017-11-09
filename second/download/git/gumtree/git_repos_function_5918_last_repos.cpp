static inline void mark_next_object(struct object *object)
{
	mark_object(object, ++last_idnum);
}