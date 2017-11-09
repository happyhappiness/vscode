apr_status_t h2_beam_receive(h2_bucket_beam *beam, 
                             apr_bucket_brigade *bb, 
                             apr_read_type_e block,
                             apr_off_t readbytes)
{
    h2_beam_lock bl;
    apr_bucket *bsender, *brecv, *ng;
    int transferred = 0;
    apr_status_t status = APR_SUCCESS;
    apr_off_t remain = readbytes;
    int transferred_buckets = 0;
    
    /* Called from the receiver thread to take buckets from the beam */
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
transfer:
        if (beam->aborted) {
            recv_buffer_cleanup(beam, &bl);
            status = APR_ECONNABORTED;
            goto leave;
        }

        /* transfer enough buckets from our receiver brigade, if we have one */
        while (beam->recv_buffer
               && !APR_BRIGADE_EMPTY(beam->recv_buffer)
               && (readbytes <= 0 || remain >= 0)) {
            brecv = APR_BRIGADE_FIRST(beam->recv_buffer);
            if (readbytes > 0 && brecv->length > 0 && remain <= 0) {
                break;
            }            
            APR_BUCKET_REMOVE(brecv);
            APR_BRIGADE_INSERT_TAIL(bb, brecv);
            remain -= brecv->length;
            ++transferred;
        }

        /* transfer from our sender brigade, transforming sender buckets to
         * receiver ones until we have enough */
        while (!H2_BLIST_EMPTY(&beam->send_list) && (readbytes <= 0 || remain >= 0)) {
            bsender = H2_BLIST_FIRST(&beam->send_list);
            brecv = NULL;
            
            if (readbytes > 0 && bsender->length > 0 && remain <= 0) {
                break;
            }
                        
            if (APR_BUCKET_IS_METADATA(bsender)) {
                if (APR_BUCKET_IS_EOS(bsender)) {
                    brecv = apr_bucket_eos_create(bb->bucket_alloc);
                    beam->close_sent = 1;
                }
                else if (APR_BUCKET_IS_FLUSH(bsender)) {
                    brecv = apr_bucket_flush_create(bb->bucket_alloc);
                }
                else if (AP_BUCKET_IS_ERROR(bsender)) {
                    ap_bucket_error *eb = (ap_bucket_error *)bsender;
                    brecv = ap_bucket_error_create(eb->status, eb->data,
                                                    bb->p, bb->bucket_alloc);
                }
            }
            else if (bsender->length == 0) {
                APR_BUCKET_REMOVE(bsender);
                H2_BLIST_INSERT_TAIL(&beam->hold_list, bsender);
                continue;
            }
            else if (APR_BUCKET_IS_FILE(bsender)) {
                /* This is set aside into the target brigade pool so that 
                 * any read operation messes with that pool and not 
                 * the sender one. */
                apr_bucket_file *f = (apr_bucket_file *)bsender->data;
                apr_file_t *fd = f->fd;
                int setaside = (f->readpool != bb->p);
                
                if (setaside) {
                    status = apr_file_setaside(&fd, fd, bb->p);
                    if (status != APR_SUCCESS) {
                        goto leave;
                    }
                    ++beam->files_beamed;
                }
                ng = apr_brigade_insert_file(bb, fd, bsender->start, bsender->length, 
                                             bb->p);
#if APR_HAS_MMAP
                /* disable mmap handling as this leads to segfaults when
                 * the underlying file is changed while memory pointer has
                 * been handed out. See also PR 59348 */
                apr_bucket_file_enable_mmap(ng, 0);
#endif
                remain -= bsender->length;
                ++transferred;
                APR_BUCKET_REMOVE(bsender);
                H2_BLIST_INSERT_TAIL(&beam->hold_list, bsender);
                ++transferred;
                continue;
            }
            else {
                /* create a "receiver" standin bucket. we took care about the
                 * underlying sender bucket and its data when we placed it into
                 * the sender brigade.
                 * the beam bucket will notify us on destruction that bsender is
                 * no longer needed. */
                brecv = h2_beam_bucket_create(beam, bsender, bb->bucket_alloc,
                                               beam->buckets_sent++);
            }
            
            /* Place the sender bucket into our hold, to be destroyed when no
             * receiver bucket references it any more. */
            APR_BUCKET_REMOVE(bsender);
            H2_BLIST_INSERT_TAIL(&beam->hold_list, bsender);
            beam->received_bytes += bsender->length;
            ++transferred_buckets;
            
            if (brecv) {
                APR_BRIGADE_INSERT_TAIL(bb, brecv);
                remain -= brecv->length;
                ++transferred;
            }
            else {
                /* let outside hook determine how bucket is beamed */
                leave_yellow(beam, &bl);
                brecv = h2_beam_bucket(beam, bb, bsender);
                enter_yellow(beam, &bl);
                
                while (brecv && brecv != APR_BRIGADE_SENTINEL(bb)) {
                    ++transferred;
                    remain -= brecv->length;
                    brecv = APR_BUCKET_NEXT(brecv);
                }
            }
        }

        if (readbytes > 0 && remain < 0) {
            /* too much, put some back */
            remain = readbytes;
            for (brecv = APR_BRIGADE_FIRST(bb);
                 brecv != APR_BRIGADE_SENTINEL(bb);
                 brecv = APR_BUCKET_NEXT(brecv)) {
                remain -= (beam->tx_mem_limits? bucket_mem_used(brecv) 
                           : brecv->length);
                if (remain < 0) {
                    apr_bucket_split(brecv, brecv->length+remain);
                    beam->recv_buffer = apr_brigade_split_ex(bb, 
                                                             APR_BUCKET_NEXT(brecv), 
                                                             beam->recv_buffer);
                    break;
                }
            }
        }

        if (transferred_buckets > 0) {
           if (beam->cons_ev_cb) { 
               beam->cons_ev_cb(beam->cons_ctx, beam);
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
            if (beam->cond) {
                apr_thread_cond_broadcast(beam->cond);
            }
            status = APR_SUCCESS;
        }
        else if (beam->closed) {
            status = APR_EOF;
        }
        else if (block == APR_BLOCK_READ && bl.mutex && beam->cond) {
            status = wait_cond(beam, bl.mutex);
            if (status != APR_SUCCESS) {
                goto leave;
            }
            goto transfer;
        }
        else {
            if (beam->cond) {
                apr_thread_cond_broadcast(beam->cond);
            }
            status = APR_EAGAIN;
        }
leave:        
        leave_yellow(beam, &bl);
    }
    return status;
}