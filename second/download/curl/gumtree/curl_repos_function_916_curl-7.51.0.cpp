void vms_special_exit(int code, int vms_show)
{
  int vms_code;

  /* The Posix exit mode is only available after VMS 7.0 */
#if __CRTL_VER >= 70000000
  if(is_vms_shell() == 0) {
    decc$__posix_exit(code);
  }
#endif

  if(code > CURL_LAST) {   /* If CURL_LAST exceeded then */
    vms_code = CURL_LAST;  /* curlmsg.h is out of sync.  */
  }
  else {
    vms_code = vms_cond[code] | vms_show;
  }
  decc$exit(vms_code);
}