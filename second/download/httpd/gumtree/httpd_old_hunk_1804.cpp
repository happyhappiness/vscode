        }
    }

    return NULL;
}

/*
 * Note what data should be used when forming file ETag values.
 * It would be nicer to do this as an ITERATE, but then we couldn't
 * remember the +/- state properly.
 */
static const char *set_etag_bits(cmd_parms *cmd, void *mconfig,
