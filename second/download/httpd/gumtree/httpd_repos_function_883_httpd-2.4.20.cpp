static int ssl_pk_server_compatible(modssl_pk_server_t *pks1, 
                                    modssl_pk_server_t *pks2) 
{
    if (!pks1 || !pks2) {
        return 0;
    }
    /* both have the same certificates? */
    if ((pks1->ca_name_path != pks2->ca_name_path)
        && (!pks1->ca_name_path || !pks2->ca_name_path 
            || strcmp(pks1->ca_name_path, pks2->ca_name_path))) {
        return 0;
    }
    if ((pks1->ca_name_file != pks2->ca_name_file)
        && (!pks1->ca_name_file || !pks2->ca_name_file 
            || strcmp(pks1->ca_name_file, pks2->ca_name_file))) {
        return 0;
    }
    if (!ap_array_same_str_set(pks1->cert_files, pks2->cert_files)
        || !ap_array_same_str_set(pks1->key_files, pks2->key_files)) {
        return 0;
    }
    return 1;
}