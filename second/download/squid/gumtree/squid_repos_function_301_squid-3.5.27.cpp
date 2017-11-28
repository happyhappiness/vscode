HRESULT
GetLPBYTEtoOctetString(VARIANT * pVar, LPBYTE * ppByte)
{
    HRESULT hr = E_FAIL;
    void HUGEP *pArray;
    long lLBound, lUBound, cElements;

    if ((!pVar) || (!ppByte))
        return E_INVALIDARG;
    if ((pVar->n1.n2.vt) != (VT_UI1 | VT_ARRAY))
        return E_INVALIDARG;

    hr = SafeArrayGetLBound(V_ARRAY(pVar), 1, &lLBound);
    hr = SafeArrayGetUBound(V_ARRAY(pVar), 1, &lUBound);

    cElements = lUBound - lLBound + 1;
    hr = SafeArrayAccessData(V_ARRAY(pVar), &pArray);
    if (SUCCEEDED(hr)) {
        LPBYTE pTemp = (LPBYTE) pArray;
        *ppByte = (LPBYTE) CoTaskMemAlloc(cElements);
        if (*ppByte)
            memcpy(*ppByte, pTemp, cElements);
        else
            hr = E_OUTOFMEMORY;
    }
    SafeArrayUnaccessData(V_ARRAY(pVar));

    return hr;
}