apr_status_t h2_beam_receive(h2_bucket_beam *beam, 
                             apr_bucket_brigade *bb, 
                             apr_read_type_e block,
                             apr_off_t readbytes)
{
    h2_beam_lock bl;
    apr_bucket *bred, *bgreen, *ng;
    int transferred = 0;
    apr_status_t status = APR_SUCCESS;
    apr_off_t remain = readbytes;
    
    /* Called from the green thread to take buckets from the beam */
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
transfer:
        if (beam->aborted) {
            if (beam->recv_buffer && !APR_BRIGADE_EMPTY(beam->recv_buffer)) {
                apr_brigade_cleanup(beam->recv_buffer);
            }
            status = APR_ECONNABORTED;
            goto leave;
        }

        /* transfer enough buckets from our green brigade, if we have one */
        beam_set_recv_pool(beam, bb->p);
        while (beam->recv_buffer
               && !APR_BRIGADE_EMPTY(beam->recv_buffer)
               && (readbytes <= 0 || remain >= 0)) {
            bgreen = APR_BRIGADE_FIRST(beam->recv_buffer);
            if (readbytes > 0 && bgreen->length > 0 && remain <= 0) {
                break;
            }            
            APR_BUCKET_REMOVE(bgreen);
            APR_BRIGADE_INSERT_TAIL(bb, bgreen);
            remain -= bgreen->length;
            ++transferred;
        }

        /* transfer from our red brigade, transforming red buckets to
         * green ones until we have enough */
        while (!H2_BLIST_EMPTY(&beam->send_list) && (readbytes <= 0 || remain >= 0)) {
            bred = H2_BLIST_FIRST(&beam->send_list);
            bgreen = NULL;
            
            if (readbytes > 0 && bred->length > 0 && remain <= 0) {
                break;
            }
                        
            if (APR_BUCKET_IS_METADATA(bred)) {
                if (APR_BUCKET_IS_EOS(bred)) {
                    bgreen = apr_bucket_eos_create(bb->bucket_alloc);
                    beam->close_sent = 1;
                }
                else if (APR_BUCKET_IS_FLUSH(bred)) {
                    bgreen = apr_bucket_flush_create(bb->bucket_alloc);
                }
                else if (AP_BUCKET_IS_ERROR(bred)) {
                    ap_bucket_error *eb = (ap_bucket_error *)bred;
                    bgreen = ap_bucket_error_create(eb->status, eb->data,
                                                    bb->p, bb->bucket_alloc);
                }
            }
            else if (APR_BUCKET_IS_FILE(bred)) {
                /* This is set aside into the target brigade pool so that 
                 * any read operation messes with that pool and not 
                 * the red one. */
                apr_bucket_file *f = (apr_bucket_file *)bred->data;
                apr_file_t *fd = f->fd;
                int setaside = (f->readpool != bb->p);
                
                if (setaside) {
                    status = apr_file_setaside(&fd, fd, bb->p);
                    if (status != APR_SUCCESS) {
                        goto leave;
                    }
                    ++beam->files_beamed;
                }
                ng = apr_brigade_insert_file(bb, fd, bred->start, bred->length, 
                                             bb->p);
#if APR_HAS_MMAP
                /* disable mmap handling as this leads to segfaults when
                 * the underlying file is changed while memory pointer has
                 * been handed out. See also PR 59348 */
                apr_bucket_file_enable_mmap(ng, 0);
#endif
                remain -= bred->length;
                ++transferred;
                APR_BUCKET_REMOVE(bred);
                H2_BLIST_INSERT_TAIL(&beam->hold_list, bred);
                ++transferred;
                continue;
            }
            else {
                /* create a "green" standin bucket. we took care about the
                 * underlying red bucket and its data when we placed it into
                 * the red brigade.
                 * the beam bucket will notify us on destruction that bred is
                 * no longer needed. */
                bgreen = h2_beam_bucket_create(beam, bred, bb->bucket_alloc,
                                               beam->buckets_sent++);
            }
            
            /* Place the red bucket into our hold, to be destroyed when no
             * green bucket references it any more. */
            APR_BUCKET_REMOVE(bred);
            H2_BLIST_INSERT_TAIL(&beam->hold_list, bred);
            beam->received_bytes += bred->length;
            if (bgreen) {
                APR_BRIGADE_INSERT_TAIL(bb, bgreen);
                remain -= bgreen->length;
                ++transferred;
            }
            else {
                bgreen = h2_beam_bucket(beam, bb, bred);
                while (bgreen && bgreen != APR_BRIGADE_SENTINEL(bb)) {
                    ++transferred;
                    remain -= bgreen->length;
                    bgreen = APR_BUCKET_NEXT(bgreen);
                }
            }
        }

        if (readbytes > 0 && remain < 0) {
            /* too much, put some back */
            remain = readbytes;
            for (bgreen = APR_BRIGADE_FIRST(bb);
                 bgreen != APR_BRIGADE_SENTINEL(bb);
                 bgreen = APR_BUCKET_NEXT(bgreen)) {
                 remain -= bgreen->length;
                 if (remain < 0) {
                     apr_bucket_split(bgreen, bgreen->length+remain);
                     beam->recv_buffer = apr_brigade_split_ex(bb, 
                                                        APR_BUCKET_NEXT(bgreen), 
                                                        beam->recv_buffer);
                     break;
                 }
            }
        }

        if (beam->closed 
            && (!beam->recv_buffer || APR_BRIGADE_EMPTY(beam->recv_buffer))
            && H2_BLIST_EMPTY(&beam->send_list)) {
            /* beam is closed and we have nothing more to receive */ 
            if (!beam->close_sent) {
                apr_bucket *b = apr_bucket_eos_create(bb->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, b);
                beam->close_sent = 1;
                ++transferred;
                status = APR_SUCCESS;
            }
        }
        
        if (transferred) {
            if (beam->m_cond) {
                apr_thread_cond_broadcast(beam->m_cond);
            }
            status = APR_SUCCESS;
        }
        else if (beam->closed) {
            status = APR_EOF;
        }
        else if (block == APR_BLOCK_READ && bl.mutex && beam->m_cond) {
            status = wait_cond(beam, bl.mutex);
            if (status != APR_SUCCESS) {
                goto leave;
            }
            goto transfer;
        }
        else {
            if (beam->m_cond) {
                apr_thread_cond_broadcast(beam->m_cond);
            }
            status = APR_EAGAIN;
        }
leave:        
        leave_yellow(beam, &bl);
    }
    return status;
}