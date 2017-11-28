HRESULT
Recursive_Memberof(IADs * pObj)
{
    VARIANT var;
    long lBound, uBound;
    HRESULT hr;

    VariantInit(&var);
    hr = pObj->lpVtbl->Get(pObj, L"memberOf", &var);
    if (SUCCEEDED(hr)) {
        if (VT_BSTR == var.n1.n2.vt) {
            if (add_User_Group(var.n1.n2.n3.bstrVal)) {
                wchar_t *Group_Path;
                IADs *pGrp;

                Group_Path = GetLDAPPath(var.n1.n2.n3.bstrVal, GC_MODE);
                hr = ADsGetObject(Group_Path, &IID_IADs, (void **) &pGrp);
                if (SUCCEEDED(hr)) {
                    hr = Recursive_Memberof(pGrp);
                    pGrp->lpVtbl->Release(pGrp);
                    safe_free(Group_Path);
                    Group_Path = GetLDAPPath(var.n1.n2.n3.bstrVal, LDAP_MODE);
                    hr = ADsGetObject(Group_Path, &IID_IADs, (void **) &pGrp);
                    if (SUCCEEDED(hr)) {
                        hr = Recursive_Memberof(pGrp);
                        pGrp->lpVtbl->Release(pGrp);
                    } else
                        debug("Recursive_Memberof: ERROR ADsGetObject for %S failed: %s\n", Group_Path, Get_WIN32_ErrorMessage(hr));
                } else
                    debug("Recursive_Memberof: ERROR ADsGetObject for %S failed: %s\n", Group_Path, Get_WIN32_ErrorMessage(hr));
                safe_free(Group_Path);
            }
        } else {
            if (SUCCEEDED(SafeArrayGetLBound(V_ARRAY(&var), 1, &lBound)) &&
                    SUCCEEDED(SafeArrayGetUBound(V_ARRAY(&var), 1, &uBound))) {
                VARIANT elem;
                while (lBound <= uBound) {
                    hr = SafeArrayGetElement(V_ARRAY(&var), &lBound, &elem);
                    if (SUCCEEDED(hr)) {
                        if (add_User_Group(elem.n1.n2.n3.bstrVal)) {
                            wchar_t *Group_Path;
                            IADs *pGrp;

                            Group_Path = GetLDAPPath(elem.n1.n2.n3.bstrVal, GC_MODE);
                            hr = ADsGetObject(Group_Path, &IID_IADs, (void **) &pGrp);
                            if (SUCCEEDED(hr)) {
                                hr = Recursive_Memberof(pGrp);
                                pGrp->lpVtbl->Release(pGrp);
                                safe_free(Group_Path);
                                Group_Path = GetLDAPPath(elem.n1.n2.n3.bstrVal, LDAP_MODE);
                                hr = ADsGetObject(Group_Path, &IID_IADs, (void **) &pGrp);
                                if (SUCCEEDED(hr)) {
                                    hr = Recursive_Memberof(pGrp);
                                    pGrp->lpVtbl->Release(pGrp);
                                    safe_free(Group_Path);
                                } else
                                    debug("Recursive_Memberof: ERROR ADsGetObject for %S failed: %s\n", Group_Path, Get_WIN32_ErrorMessage(hr));
                            } else
                                debug("Recursive_Memberof: ERROR ADsGetObject for %S failed: %s\n", Group_Path, Get_WIN32_ErrorMessage(hr));
                            safe_free(Group_Path);
                        }
                        VariantClear(&elem);
                    } else {
                        debug("Recursive_Memberof: ERROR SafeArrayGetElement failed: %s\n", Get_WIN32_ErrorMessage(hr));
                        VariantClear(&elem);
                    }
                    ++lBound;
                }
            } else
                debug("Recursive_Memberof: ERROR SafeArrayGetxBound failed: %s\n", Get_WIN32_ErrorMessage(hr));
        }
        VariantClear(&var);
    } else {
        if (hr != E_ADS_PROPERTY_NOT_FOUND)
            debug("Recursive_Memberof: ERROR getting memberof attribute: %s\n", Get_WIN32_ErrorMessage(hr));
    }
    return hr;
}