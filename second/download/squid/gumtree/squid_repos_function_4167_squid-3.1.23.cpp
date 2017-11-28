bool
ACLTimeData::match(time_t when)
{
    static time_t last_when = 0;

    static struct tm tm;
    time_t t;

    if (when != last_when) {
        last_when = when;

        xmemcpy(&tm, localtime(&when), sizeof(struct tm));
    }

    t = (time_t) (tm.tm_hour * 60 + tm.tm_min);
    ACLTimeData *data = this;

    while (data) {
        debugs(28, 3, "aclMatchTime: checking " << t  << " in " <<
               data->start  << "-" << data->stop  << ", weekbits=" <<
               std::hex << data->weekbits);

        if (t >= data->start && t <= data->stop && (data->weekbits & (1 << tm.tm_wday)))
            return 1;

        data = data->next;
    }

    return 0;
}