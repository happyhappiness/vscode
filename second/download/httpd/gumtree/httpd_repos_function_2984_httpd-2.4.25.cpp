static apr_status_t execute(sed_eval_t *eval)
{
    sed_reptr_t *ipc = eval->commands->ptrspace;
    step_vars_storage step_vars;
    apr_status_t rv = APR_SUCCESS;

    eval->lnum++;

    eval->sflag = 0;

    if (eval->pending) {
        ipc = eval->pending;
        eval->pending = NULL;
    }

    memset(&step_vars, 0, sizeof(step_vars));

    while (ipc->command) {
        char *p1;
        char *p2;
        int c;

        p1 = ipc->ad1;
        p2 = ipc->ad2;

        if (p1) {

            if (eval->inar[ipc->nrep]) {
                if (*p2 == CEND) {
                    p1 = 0;
                } else if (*p2 == CLNUM) {
                    c = (unsigned char)p2[1];
                    if (eval->lnum > eval->commands->tlno[c]) {
                        eval->inar[ipc->nrep] = 0;
                        if (ipc->negfl)
                            goto yes;
                        ipc = ipc->next;
                        continue;
                    }
                    if (eval->lnum == eval->commands->tlno[c]) {
                        eval->inar[ipc->nrep] = 0;
                    }
                } else if (match(eval, p2, 0, &step_vars)) {
                    eval->inar[ipc->nrep] = 0;
                }
            } else if (*p1 == CEND) {
                if (!eval->dolflag) {
                    if (ipc->negfl)
                        goto yes;
                    ipc = ipc->next;
                    continue;
                }
            } else if (*p1 == CLNUM) {
                c = (unsigned char)p1[1];
                if (eval->lnum != eval->commands->tlno[c]) {
                    if (ipc->negfl)
                        goto yes;
                    ipc = ipc->next;
                    continue;
                }
                if (p2)
                    eval->inar[ipc->nrep] = 1;
            } else if (match(eval, p1, 0, &step_vars)) {
                if (p2)
                    eval->inar[ipc->nrep] = 1;
            } else {
                if (ipc->negfl)
                    goto yes;
                ipc = ipc->next;
                continue;
            }
        }

        if (ipc->negfl) {
            ipc = ipc->next;
            continue;
        }

yes:
        rv = command(eval, ipc, &step_vars);
        if (rv != APR_SUCCESS)
            return rv;

        if (eval->quitflag)
            return APR_SUCCESS;

        if (eval->pending)
            return APR_SUCCESS;

        if (eval->delflag)
            break;

        if (eval->jflag) {
            eval->jflag = 0;
            if ((ipc = ipc->lb1) == 0) {
                ipc = eval->commands->ptrspace;
                break;
            }
        } else
            ipc = ipc->next;
    }

    if (!eval->commands->nflag && !eval->delflag) {
        rv = wline(eval, eval->linebuf, eval->lspend - eval->linebuf);
        if (rv != APR_SUCCESS)
            return rv;
    }

    if (eval->aptr > eval->abuf)
        rv = arout(eval);

    eval->delflag = 0;

    eval->lspend = eval->linebuf;

    return rv;
}