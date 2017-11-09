unsigned char curlx_uitouc(unsigned int uinum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(uinum <= (unsigned int) CURL_MASK_UCHAR);
  return (unsigned char) (uinum & (unsigned int) CURL_MASK_UCHAR);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}