
    err_type page_id =
        aclGetDenyInfoPage(&Config.denyInfoList, answer.ruleId.termedBuf(), 1);
    if (page_id == ERR_NONE)
        page_id = ERR_ACCESS_DENIED;

    ErrorState *err = new ErrorState(page_id, Http::scForbidden, request);
    err->detailError(ERR_DETAIL_RESPMOD_BLOCK_EARLY);
    fwd->fail(err);
    fwd->dontRetry(true);

    abortTransaction("timely adaptation block");
}
