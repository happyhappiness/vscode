static apr_time_t get_request_end_time(request_rec *r)
{
    log_request_state *state = (log_request_state *)ap_get_module_config(r->request_config,
                                                                         &log_config_module);
    if (!state) {
        state = apr_pcalloc(r->pool, sizeof(log_request_state));
        ap_set_module_config(r->request_config, &log_config_module, state);
    }
    if (state->request_end_time == 0) {
        state->request_end_time = apr_time_now();
    }
    return state->request_end_time;
}