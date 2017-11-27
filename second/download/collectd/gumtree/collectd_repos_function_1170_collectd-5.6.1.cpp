static char const *mosquitto_strerror (int code)
{
    switch (code)
    {
        case MOSQ_ERR_SUCCESS: return "MOSQ_ERR_SUCCESS";
        case MOSQ_ERR_NOMEM: return "MOSQ_ERR_NOMEM";
        case MOSQ_ERR_PROTOCOL: return "MOSQ_ERR_PROTOCOL";
        case MOSQ_ERR_INVAL: return "MOSQ_ERR_INVAL";
        case MOSQ_ERR_NO_CONN: return "MOSQ_ERR_NO_CONN";
        case MOSQ_ERR_CONN_REFUSED: return "MOSQ_ERR_CONN_REFUSED";
        case MOSQ_ERR_NOT_FOUND: return "MOSQ_ERR_NOT_FOUND";
        case MOSQ_ERR_CONN_LOST: return "MOSQ_ERR_CONN_LOST";
        case MOSQ_ERR_SSL: return "MOSQ_ERR_SSL";
        case MOSQ_ERR_PAYLOAD_SIZE: return "MOSQ_ERR_PAYLOAD_SIZE";
        case MOSQ_ERR_NOT_SUPPORTED: return "MOSQ_ERR_NOT_SUPPORTED";
        case MOSQ_ERR_AUTH: return "MOSQ_ERR_AUTH";
        case MOSQ_ERR_ACL_DENIED: return "MOSQ_ERR_ACL_DENIED";
        case MOSQ_ERR_UNKNOWN: return "MOSQ_ERR_UNKNOWN";
        case MOSQ_ERR_ERRNO: return "MOSQ_ERR_ERRNO";
    }

    return "UNKNOWN ERROR CODE";
}