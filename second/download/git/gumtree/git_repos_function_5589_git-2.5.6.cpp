static int check_offset_overflow(off_t offset, uintmax_t len)
{
	if (len > maximum_signed_value_of_type(off_t))
		return error("unrepresentable length in delta: "
				"%"PRIuMAX" > OFF_MAX", len);
	if (signed_add_overflows(offset, (off_t) len))
		return error("unrepresentable offset in delta: "
				"%"PRIuMAX" + %"PRIuMAX" > OFF_MAX",
				(uintmax_t) offset, len);
	return 0;
}