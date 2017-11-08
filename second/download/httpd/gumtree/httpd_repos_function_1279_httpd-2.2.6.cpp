static ap_unix_identity_t *cgid_suexec_id_doer(const request_rec *r)
{
    return (ap_unix_identity_t *)
                        ap_get_module_config(r->request_config, &cgid_module);
}