                                                  w->name, s,
                                                  wd_server_conf->pool, 0);
                        if (rv != APR_SUCCESS) {
                            return rv;
                        }
                    }
                    wd_server_conf->child_workers++;
                }
            }
        }
    }
    return OK;
