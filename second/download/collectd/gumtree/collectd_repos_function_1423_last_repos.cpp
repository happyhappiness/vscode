static int mc_handle_metric(void *buffer, size_t buffer_size) /* {{{ */
{
  XDR xdr;
  Ganglia_msg_formats format;

  xdrmem_create(&xdr, buffer, buffer_size, XDR_DECODE);

  xdr_Ganglia_msg_formats(&xdr, &format);
  xdr_setpos(&xdr, 0);

  switch (format) {
  case gmetric_ushort:
  case gmetric_short:
  case gmetric_int:
  case gmetric_uint:
  case gmetric_string:
  case gmetric_float:
  case gmetric_double: {
    Ganglia_value_msg msg = {0};

    if (xdr_Ganglia_value_msg(&xdr, &msg))
      mc_handle_value_msg(&msg);
    break;
  }

  case gmetadata_full:
  case gmetadata_request: {
    Ganglia_metadata_msg msg = {0};
    if (xdr_Ganglia_metadata_msg(&xdr, &msg))
      mc_handle_metadata_msg(&msg);
    break;
  }

  default:
    DEBUG("gmond plugin: Unknown format: %i", format);
    return -1;
  } /* switch (format) */

  return 0;
}