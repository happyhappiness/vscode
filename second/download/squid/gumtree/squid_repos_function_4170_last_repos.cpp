static
ACL *
Make(TypeName typeName)
{
    const auto pos = TheMakers().find(typeName);
    if (pos == TheMakers().end()) {
        debugs(28, DBG_CRITICAL, "FATAL: Invalid ACL type '" << typeName << "'");
        self_destruct();
        assert(false); // not reached
    }

    ACL *result = (pos->second)(pos->first);
    debugs(28, 4, typeName << '=' << result);
    assert(result);
    return result;
}