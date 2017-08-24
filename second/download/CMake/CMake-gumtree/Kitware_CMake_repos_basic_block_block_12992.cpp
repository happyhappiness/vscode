{
			w->pool.len = ((fnam.len + 64U) / 64U) * 64U;
			w->pool.str = realloc(w->pool.str, w->pool.len);
		}