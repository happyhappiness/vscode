(i = 0; i < a->client.nodes; i++)
					(a->client.closer)(&a->archive,
					    a->client.dataset[i].data)