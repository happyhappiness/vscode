void
FwdState::fail(ErrorState * errorState)
{
    debugs(17, 3, HERE << err_type_str[errorState->type] << " \"" << httpStatusString(errorState->httpStatus) << "\"\n\t" << entry->url()  );

    if (err)
        errorStateFree(err);

    err = errorState;

    if (!errorState->request)
        errorState->request = HTTPMSGLOCK(request);
}