addReplyStatusFormat(c,
                "Value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld",
                (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL));