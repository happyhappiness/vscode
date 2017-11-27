static int cna_setup_quota(cfg_quota_t *cq) /* {{{ */
{
  if (cq == NULL)
    return EINVAL;

  if (cq->query != NULL)
    return 0;

  cq->query = na_elem_new("quota-report");
  if (cq->query == NULL) {
    ERROR("netapp plugin: na_elem_new failed.");
    return -1;
  }

  return 0;
}