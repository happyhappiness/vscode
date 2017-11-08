static apr_status_t simple_main_setup_timers(simple_core_t * sc)
{
    simple_register_timer(sc, simple_check_children_size, NULL, 0, sc->pool);

    return APR_SUCCESS;
}