const char *ajp_type_str(int type)
{
    switch (type) {
        case_to_str(FORWARD_REQUEST)
        case_to_str(SEND_BODY_CHUNK)
        case_to_str(SEND_HEADERS)
        case_to_str(END_RESPONSE)
        case_to_str(GET_BODY_CHUNK)
        case_to_str(SHUTDOWN)
        case_to_str(PING)
        case_to_str(CPONG)
        case_to_str(CPING)
        default:
            return "CMD_AJP13_UNKNOWN";
    }

}