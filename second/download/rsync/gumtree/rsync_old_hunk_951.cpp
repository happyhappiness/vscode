			send_msg_int(MSG_SUCCESS, ndx);
	}

	if (inc_recurse) {
		int gnum = F_HL_GNUM(file);
		struct ht_int32_node *node = hashtable_find(prior_hlinks, gnum, 0);
		assert(node != NULL && node->data != NULL);
		assert(CVAL(node->data, 0) == 0);
		free(node->data);
		if (!(node->data = strdup(our_name)))
			out_of_memory("finish_hard_link");
	}
}

