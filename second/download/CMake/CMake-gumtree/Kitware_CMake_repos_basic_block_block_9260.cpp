{
		a->client.dataset[i].data = a->client.dataset[i-1].data;
		a->client.dataset[i].begin_position = -1;
		a->client.dataset[i].total_size = -1;
	}