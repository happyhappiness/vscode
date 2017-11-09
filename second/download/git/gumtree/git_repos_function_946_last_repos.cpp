static inline int column_active(unsigned int colopts)
{
	return (colopts & COL_ENABLE_MASK) == COL_ENABLED;
}