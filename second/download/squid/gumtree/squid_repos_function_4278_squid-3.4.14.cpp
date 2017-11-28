static int asn1time_cmp(ASN1_TIME *asnTime1, ASN1_TIME *asnTime2)
{
    char strTime1[64], strTime2[64];
    if (!asn1timeToGeneralizedTimeStr(asnTime1, strTime1, sizeof(strTime1)))
        return -1;
    if (!asn1timeToGeneralizedTimeStr(asnTime2, strTime2, sizeof(strTime2)))
        return -1;

    return strcmp(strTime1, strTime2);
}