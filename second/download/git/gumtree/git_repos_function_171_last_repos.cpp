static inline struct child_process *subprocess_get_child_process(
		struct subprocess_entry *entry)
{
	return &entry->process;
}