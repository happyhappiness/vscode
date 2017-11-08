static apr_status_t asio_pollset_cleanup(apr_pollset_t *pollset)
{
    DBG_BUFF
    int rv;

    DBG(4, "entered\n");
    rv = msgctl(pollset->p->msg_q, IPC_RMID, NULL);

    DBG1(4, "exiting, msgctl(IPC_RMID) returned %d\n", rv);
    return rv;
}