void dnstop_set_callback (void (*cb) (const rfc1035_header_t *))
{
	Callback = cb;
}