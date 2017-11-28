void
Comm::ConnOpener::sendAnswer(comm_err_t errFlag, int xerrno, const char *why)
{
    // only mark the address good/bad AFTER connect is finished.
    if (host_ != NULL) {
        if (xerrno == 0) // XXX: should not we use errFlag instead?
            ipcacheMarkGoodAddr(host_, conn_->remote);
        else {
            ipcacheMarkBadAddr(host_, conn_->remote);
#if USE_ICMP
            if (Config.onoff.test_reachability)
                netdbDeleteAddrNetwork(conn_->remote);
#endif
        }
    }

    if (callback_ != NULL) {
        // avoid scheduling cancelled callbacks, assuming they are common
        // enough to make this extra check an optimization
        if (callback_->canceled()) {
            debugs(5, 4, conn_ << " not calling canceled " << *callback_ <<
                   " [" << callback_->id << ']' );
            // TODO save the pconn to the pconnPool ?
        } else {
            typedef CommConnectCbParams Params;
            Params &params = GetCommParams<Params>(callback_);
            params.conn = conn_;
            params.flag = errFlag;
            params.xerrno = xerrno;
            ScheduleCallHere(callback_);
        }
        callback_ = NULL;
    }

    // The job will stop without this call because nil callback_ makes
    // doneAll() true, but this explicit call creates nicer debugging.
    mustStop(why);
}