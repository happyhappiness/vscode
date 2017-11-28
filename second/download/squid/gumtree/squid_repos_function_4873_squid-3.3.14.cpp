void
Rock::IoState::callBack(int errflag)
{
    debugs(79,3, HERE << "errflag=" << errflag);
    theFile = NULL;

    AsyncCall::Pointer call = asyncCall(79,3, "SomeIoStateCloseCb",
                                        StoreIOStateCb(callback, callback_data, errflag, this));
    ScheduleCallHere(call);

    callback = NULL;
    cbdataReferenceDone(callback_data);
}