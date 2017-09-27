 * In filter->ctx, the callback will find its context. This context is
 * provided here, so that a filter may be installed multiple times, each
 * receiving its own per-install context pointer.
 *
 * Callbacks are associated with a filter definition, which is specified
 * by name. See ap_register_input_filter() and ap_register_output_filter()
 * for setting the association between a name for a filter and its 
 * associated callback (and other information).
 *
 * If the initialization function argument passed to the registration
 * functions is non-NULL, it will be called iff the filter is in the input
 * or output filter chains and before any data is generated to allow the
 * filter to prepare for processing.
