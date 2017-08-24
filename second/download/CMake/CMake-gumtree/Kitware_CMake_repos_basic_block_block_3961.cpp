{
    result = (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
              /* The other multi errors should never happen, so return
                 something suitably generic */
              CURLE_BAD_FUNCTION_ARGUMENT;
  }