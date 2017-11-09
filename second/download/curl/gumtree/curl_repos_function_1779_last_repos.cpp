unsigned int curlx_uztoui(size_t uznum)
{
#ifdef __INTEL_COMPILER
# pragma warning(push)
# pragma warning(disable:810) /* conversion may lose significant bits */
#endif

#if (SIZEOF_INT < SIZEOF_SIZE_T)
  DEBUGASSERT(uznum <= (size_t) CURL_MASK_UINT);
#endif
  return (unsigned int)(uznum & (size_t) CURL_MASK_UINT);

#ifdef __INTEL_COMPILER
# pragma warning(pop)
#endif
}