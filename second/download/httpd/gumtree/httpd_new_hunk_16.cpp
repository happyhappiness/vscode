        client_list->table[bucket] = entry;
    }

    apr_global_mutex_unlock(client_lock);

    if (entry) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "get_client(): client %lu found", key);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "get_client(): client %lu not found", key);
    }

    return entry;
}

