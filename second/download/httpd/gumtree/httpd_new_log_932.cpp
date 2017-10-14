apr_psprintf(p, "Module \"%s\" could not be loaded, "
                                "because the dynamic module limit was "
                                "reached. Please increase "
                                "DYNAMIC_MODULE_LIMIT and recompile.", m->name);