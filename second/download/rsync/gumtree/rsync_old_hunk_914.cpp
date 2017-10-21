		assert(CVAL(node->data, 0) == 0);
		free(node->data);
		if (!(node->data = strdup(our_name)))
			out_of_memory("finish_hard_link");
	}
}
#endif
