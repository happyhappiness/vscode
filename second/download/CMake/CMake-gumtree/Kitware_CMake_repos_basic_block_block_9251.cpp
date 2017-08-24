(i = 0; i < self->archive->client.nodes; i++)
	{
		r2 = (self->archive->client.closer)
			((struct archive *)self->archive,
				self->archive->client.dataset[i].data);
		if (r > r2)
			r = r2;
	}