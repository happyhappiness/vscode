static inline unsigned int
iptcb_offset2index(const TC_HANDLE_T h, unsigned int offset)
{
	return iptcb_entry2index(h, iptcb_offset2entry(h, offset));
}