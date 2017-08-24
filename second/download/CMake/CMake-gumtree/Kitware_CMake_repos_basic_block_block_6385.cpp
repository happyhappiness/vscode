f(nego->status == SEC_I_COMPLETE_NEEDED ||
     nego->status == SEC_I_COMPLETE_AND_CONTINUE) {
    nego->status = s_pSecFn->CompleteAuthToken(nego->context, &resp_desc);
    if(GSS_ERROR(nego->status)) {
      return CURLE_RECV_ERROR;
    }
  }