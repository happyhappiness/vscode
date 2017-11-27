static void job_stats_submit(virDomainPtr domain, virTypedParameterPtr param) {
  value_t vl = {0};

  if (param->type == VIR_TYPED_PARAM_INT)
    vl.derive = param->value.i;
  else if (param->type == VIR_TYPED_PARAM_UINT)
    vl.derive = param->value.ui;
  else if (param->type == VIR_TYPED_PARAM_LLONG)
    vl.derive = param->value.l;
  else if (param->type == VIR_TYPED_PARAM_ULLONG)
    vl.derive = param->value.ul;
  else if (param->type == VIR_TYPED_PARAM_DOUBLE)
    vl.derive = param->value.d;
  else if (param->type == VIR_TYPED_PARAM_BOOLEAN)
    vl.derive = param->value.b;
  else if (param->type == VIR_TYPED_PARAM_STRING) {
    submit_notif(domain, NOTIF_OKAY, param->value.s, "job_stats", param->field);
    return;
  } else {
    ERROR(PLUGIN_NAME " plugin: unrecognized virTypedParameterType");
    return;
  }

  submit(domain, "job_stats", param->field, &vl, 1);
}