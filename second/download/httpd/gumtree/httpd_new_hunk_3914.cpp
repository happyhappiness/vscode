                /* This happens currently when ap_die(status, r) is invoked
                 * by a read request filter.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                              "h2_task_output(%s): write without response "
                              "for %s %s %s",
                              output->task->id, output->task->request->method, 
                              output->task->request->authority, 
                              output->task->request->path);
                f->c->aborted = 1;
            }
            if (output->task->io) {
                apr_thread_cond_broadcast(output->task->io);
            }
            return APR_ECONNABORTED;
        }
        
        output->trailers_passed = !!response->trailers;
        return h2_mplx_out_open(output->task->mplx, output->task->stream_id, 
                                response, f, bb, output->task->io);
    }
    return APR_EOF;
}

static apr_table_t *get_trailers(h2_task_output *output)
{
    if (!output->trailers_passed) {
        h2_response *response = h2_from_h1_get_response(output->from_h1);
        if (response && response->trailers) {
            output->trailers_passed = 1;
            return response->trailers;
        }
    }
    return NULL;
}

void h2_task_output_close(h2_task_output *output)
{
    open_if_needed(output, NULL, NULL);
    if (output->state != H2_TASK_OUT_DONE) {
        h2_mplx_out_close(output->task->mplx, output->task->stream_id, 
                          get_trailers(output));
        output->state = H2_TASK_OUT_DONE;
    }
}

int h2_task_output_has_started(h2_task_output *output)
{
