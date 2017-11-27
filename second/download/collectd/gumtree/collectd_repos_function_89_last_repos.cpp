static int get_domain_state(virDomainPtr domain) {
  int domain_state = 0;
  int domain_reason = 0;

  int status = virDomainGetState(domain, &domain_state, &domain_reason, 0);
  if (status != 0) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetState failed with status %i.",
          status);
    return status;
  }

  domain_state_submit(domain, domain_state, domain_reason);
  return status;
}