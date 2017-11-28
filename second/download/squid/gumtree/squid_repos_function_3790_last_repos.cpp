static bool asn1timeToGeneralizedTimeStr(ASN1_TIME *aTime, char *buf, int bufLen)
{
    // ASN1_Time  holds time to UTCTime or GeneralizedTime form.
    // UTCTime has the form YYMMDDHHMMSS[Z | [+|-]offset]
    // GeneralizedTime has the form YYYYMMDDHHMMSS[Z | [+|-] offset]

    // length should have space for data plus 2 extra bytes for the two extra year fields
    // plus the '\0' char.
    if ((aTime->length + 3) > bufLen)
        return false;

    char *str;
    if (aTime->type == V_ASN1_UTCTIME) {
        if (aTime->data[0] > '5') { // RFC 2459, section 4.1.2.5.1
            buf[0] = '1';
            buf[1] = '9';
        } else {
            buf[0] = '2';
            buf[1] = '0';
        }
        str = buf +2;
    } else // if (aTime->type == V_ASN1_GENERALIZEDTIME)
        str = buf;

    memcpy(str, aTime->data, aTime->length);
    str[aTime->length] = '\0';
    return true;
}