        }

        return apr_psprintf(cmd->pool, "Unexpected parameter: `%s'",
                            args);
    }

    /* parsing is done...  register the filter
     */
    if (filter->mode == OUTPUT_FILTER) {
        /* XXX need a way to ensure uniqueness among all filters */
        ap_register_output_filter(filter->name, ef_output_filter, NULL, filter->ftype);
    }
    else if (filter->mode == INPUT_FILTER) {
        /* XXX need a way to ensure uniqueness among all filters */
        ap_register_input_filter(filter->name, ef_input_filter, NULL, filter->ftype);
    }
    else {
        ap_assert(1 != 1); /* we set the field wrong somehow */
    }

    return NULL;
}
