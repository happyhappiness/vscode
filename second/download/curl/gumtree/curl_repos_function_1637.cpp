curl_off_t curlx_uztoso(size_t uznum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(uznum <= (size_t) CURL_MASK_SCOFFT);
  return (curl_off_t)(uznum & (size_t) CURL_MASK_SCOFFT);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}