                        /* another data bucket before this one in hold. this
                         * is normal since DATA buckets need not be destroyed
                         * in order */
                    }
                }
                
                proxy->bsender = NULL;
            }
            else {
                /* it should be there unless we screwed up */
                ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, beam->send_pool, 
                              APLOGNO(03384) "h2_beam(%d-%s): emitted bucket not "
                              "in hold, n=%d", beam->id, beam->tag, 
                              (int)proxy->n);
                ap_assert(!proxy->bsender);
            }
        }
        /* notify anyone waiting on space to become available */
        if (!bl.mutex) {
            r_purge_sent(beam);
        }
        else if (beam->cond) {
            apr_thread_cond_broadcast(beam->cond);
        }
        leave_yellow(beam, &bl);
    }
}

static void h2_blist_cleanup(h2_blist *bl)
