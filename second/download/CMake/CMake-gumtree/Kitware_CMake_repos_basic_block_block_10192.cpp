{
				__archive_read_filter_consume(self->upstream,
					state->consume_unnotified);
				state->consume_unnotified = 0;
			}