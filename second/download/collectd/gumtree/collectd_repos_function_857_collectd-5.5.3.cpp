static inline void
delta_core(struct core_data *delta, const struct core_data *new, const struct core_data *old)
{
	delta->c3 = new->c3 - old->c3;
	delta->c6 = new->c6 - old->c6;
	delta->c7 = new->c7 - old->c7;
	delta->core_temp_c = new->core_temp_c;
}