ap_rvputs(r, (*worker->s->uds_path ? "<i>" : ""), ap_proxy_worker_name(r->pool, worker),
                          (*worker->s->uds_path ? "</i>" : ""), "</a></td>", NULL);