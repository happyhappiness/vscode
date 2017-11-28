const char
*ErrLDAP(int e)
{
    switch (e) {
    case LDAP_ERR_NULL:
        return "Null pointer provided";
    case LDAP_ERR_POINTER:
        return "Null LDAP pointer";
    case LDAP_ERR_PARAM:
        return "Null or Missing paremeter(s)";
    case LDAP_ERR_INIT:
        return "LDAP data not initalized";
    case LDAP_ERR_OPEN:
        return "LDAP connection is not active";
    case LDAP_ERR_CONNECT:
        return "Unable to connect to LDAP host";
    case LDAP_ERR_BIND:
        return "LDAP connection is not bound";
    case LDAP_ERR_SEARCHED:
        return "LDAP connection has already been searched";
    case LDAP_ERR_NOT_SEARCHED:
        return "LDAP connection has not been searched";
    case LDAP_ERR_INVALID:
        return "Invalid paremeters";
    case LDAP_ERR_OOB:
        return "Paremeter is out of bounds";
    case LDAP_ERR_PERSIST:
        return "Persistent mode is not active";
    case LDAP_ERR_DATA:
        return "Required data has not been found";
    case LDAP_ERR_NOTFOUND:
        return "Item or object has not been found";
    case LDAP_ERR_OTHER:
        return "An unknown error has occured";
    case LDAP_ERR_FAILED:
        return "Operation has failed";
    case LDAP_ERR_SUCCESS:
        return "Operation is successful";
    default:
        return "An unknown error has occured";
    }
}