apr_psprintf(p, "Module \"%s\" is not compatible with this "
                            "version of Apache (found %d, need %d). Please "
                            "contact the vendor for the correct version.",
                            m->name, m->version, MODULE_MAGIC_NUMBER_MAJOR);