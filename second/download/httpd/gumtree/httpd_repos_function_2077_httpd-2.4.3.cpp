char* sed_get_finalize_error(const sed_commands_t *commands, apr_pool_t* pool)
{
    const sed_label_t *lab;
    if (commands->depth) {
        return SEDERR_TMOMES;
    }

    /* Empty branch chain is not a issue */
    for (lab = commands->labtab + 1; lab < commands->lab; lab++) {
        char *error;
        if (lab->address == 0) {
            error = apr_psprintf(pool, SEDERR_ULMES, lab->asc);
            return error;
        }

        if (lab->chain) {
            return SEDERR_INTERNAL;
        }
    }
    return NULL;
}