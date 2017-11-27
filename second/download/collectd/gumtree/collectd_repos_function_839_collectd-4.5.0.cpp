static void flush_buffer (void)
{
	DEBUG ("network plugin: flush_buffer: send_buffer_fill = %i",
			send_buffer_fill);

	network_send_buffer (send_buffer, send_buffer_fill);
	send_buffer_ptr  = send_buffer;
	send_buffer_fill = 0;
	memset (&send_buffer_vl, '\0', sizeof (send_buffer_vl));
	memset (send_buffer_type, '\0', sizeof (send_buffer_type));
}