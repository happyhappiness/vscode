static void vcpu_submit(derive_t value, virDomainPtr dom, int vcpu_nr,
                        const char *type) {
  char type_instance[DATA_MAX_NAME_LEN];

  snprintf(type_instance, sizeof(type_instance), "%d", vcpu_nr);
  submit(dom, type, type_instance, &(value_t){.derive = value}, 1);
}