apr_file_printf(out, "  %s\n",
                                APR_ARRAY_IDX(pks->cert_files,
                                              i, const char *));