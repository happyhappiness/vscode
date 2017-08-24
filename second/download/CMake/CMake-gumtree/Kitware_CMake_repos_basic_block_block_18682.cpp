(cmpxchgi(&h->pending, 1, 0) == 0)
      continue;