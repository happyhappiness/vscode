long long get_kstat_value(kstat_t *ksp, char *name) {
  kstat_named_t *kn;
  long long retval = -1LL;

  if (ksp == NULL) {
    ERROR("get_kstat_value (\"%s\"): ksp is NULL.", name);
    return -1LL;
  } else if (ksp->ks_type != KSTAT_TYPE_NAMED) {
    ERROR("get_kstat_value (\"%s\"): ksp->ks_type (%#x) "
          "is not KSTAT_TYPE_NAMED (%#x).",
          name, (unsigned int)ksp->ks_type, (unsigned int)KSTAT_TYPE_NAMED);
    return -1LL;
  }

  if ((kn = (kstat_named_t *)kstat_data_lookup(ksp, name)) == NULL)
    return -1LL;

  if (kn->data_type == KSTAT_DATA_INT32)
    retval = (long long)kn->value.i32;
  else if (kn->data_type == KSTAT_DATA_UINT32)
    retval = (long long)kn->value.ui32;
  else if (kn->data_type == KSTAT_DATA_INT64)
    retval =
        (long long)kn->value.i64; /* According to ANSI C99 `long long' must hold
                                     at least 64 bits */
  else if (kn->data_type == KSTAT_DATA_UINT64)
    retval = (long long)kn->value.ui64; /* XXX: Might overflow! */
  else
    WARNING("get_kstat_value: Not a numeric value: %s", name);

  return retval;
}