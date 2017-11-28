wchar_t *
My_NameTranslate(wchar_t * name, int in_format, int out_format)
{
    IADsNameTranslate *pNto;
    HRESULT hr;
    BSTR bstr;
    wchar_t *wc;

    if (WIN32_COM_initialized == 0) {
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            debug("My_NameTranslate: cannot initialize COM interface, ERROR: %s\n", Get_WIN32_ErrorMessage(hr));
            /* This is a fatal error */
            exit(1);
        }
        WIN32_COM_initialized = 1;
    }
    hr = CoCreateInstance(&CLSID_NameTranslate,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          &IID_IADsNameTranslate,
                          (void **) &pNto);
    if (FAILED(hr)) {
        debug("My_NameTranslate: cannot create COM instance, ERROR: %s\n", Get_WIN32_ErrorMessage(hr));
        /* This is a fatal error */
        exit(1);
    }
    hr = pNto->lpVtbl->Init(pNto, ADS_NAME_INITTYPE_GC, L"");
    if (FAILED(hr)) {
        debug("My_NameTranslate: cannot initialise NameTranslate API, ERROR: %s\n", Get_WIN32_ErrorMessage(hr));
        pNto->lpVtbl->Release(pNto);
        /* This is a fatal error */
        exit(1);
    }
    hr = pNto->lpVtbl->Set(pNto, in_format, name);
    if (FAILED(hr)) {
        debug("My_NameTranslate: cannot set translate of %S, ERROR: %s\n", name, Get_WIN32_ErrorMessage(hr));
        pNto->lpVtbl->Release(pNto);
        return NULL;
    }
    hr = pNto->lpVtbl->Get(pNto, out_format, &bstr);
    if (FAILED(hr)) {
        debug("My_NameTranslate: cannot get translate of %S, ERROR: %s\n", name, Get_WIN32_ErrorMessage(hr));
        pNto->lpVtbl->Release(pNto);
        return NULL;
    }
    debug("My_NameTranslate: %S translated to %S\n", name, bstr);

    wc = (wchar_t *) xmalloc((wcslen(bstr) + 1) * sizeof(wchar_t));
    wcscpy(wc, bstr);
    SysFreeString(bstr);
    pNto->lpVtbl->Release(pNto);
    return wc;
}