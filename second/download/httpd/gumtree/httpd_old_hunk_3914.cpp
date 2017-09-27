                /* This happens currently when ap_die(status, r) is invoked
                 * by a read request filter.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                              "h2_task_output(%s): write without response "
                              "for %s %s %s",
                              output->env->id, output->env->method, 
                              output->env->authority, output->env->path);
                f->c->aborted = 1;
            }
            if (output->env->io) {
                apr_thread_cond_broadcast(output->env->io);
            }
            return APR_ECONNABORTED;
        }
        
        return h2_mplx_out_open(output->env->mplx, output->env->stream_id, 
                                response, f, bb, output->env->io);
    }
    return APR_EOF;
}

void h2_task_output_close(h2_task_output *output)
{
    open_if_needed(output, NULL, NULL);
    if (output->state != H2_TASK_OUT_DONE) {
        h2_mplx_out_close(output->env->mplx, output->env->stream_id);
        output->state = H2_TASK_OUT_DONE;
    }
}

int h2_task_output_has_started(h2_task_output *output)
{
