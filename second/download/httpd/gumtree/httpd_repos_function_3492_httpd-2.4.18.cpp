void ap_cb_destroy(void *a)
{
    /* cleanup down event notification */
    UnRegisterEventNotification(eh);
    NX_UNWRAP_INTERFACE(ref);
    NX_UNWRAP_INTERFACE(dum);
}