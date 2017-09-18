	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    hash = TABLE_HASH(key);
    t->index_last[hash] = t->a.nelts;
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
    }
    COMPUTE_KEY_CHECKSUM(key, checksum);
    elts = (apr_table_entry_t *) table_push(t);
    elts->key = (char *)key;
    elts->val = (char *)val;
    elts->key_checksum = checksum;
}
