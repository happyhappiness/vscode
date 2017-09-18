	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    COMPUTE_KEY_CHECKSUM(key, checksum);
    elts = (apr_table_entry_t *) table_push(t);
    elts->key = (char *)key;
    elts->val = (char *)val;
    elts->key_checksum = checksum;
}
