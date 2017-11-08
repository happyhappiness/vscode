void ap_cb_destroy(void *)
{
  // cleanup down event notification
  UnRegisterEventNotification(eh);
  NX_UNWRAP_INTERFACE(ref);
  NX_UNWRAP_INTERFACE(dum);
}