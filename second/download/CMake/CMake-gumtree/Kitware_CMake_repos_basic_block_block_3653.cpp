f(result)
    /* failure, so we cancel the ares operation */
    ares_cancel((ares_channel)data->state.resolver)