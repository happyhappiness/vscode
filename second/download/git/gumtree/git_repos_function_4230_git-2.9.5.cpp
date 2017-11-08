void ewah_clear(struct ewah_bitmap *self)
{
	self->buffer_size = 1;
	self->buffer[0] = 0;
	self->bit_size = 0;
	self->rlw = self->buffer;
}