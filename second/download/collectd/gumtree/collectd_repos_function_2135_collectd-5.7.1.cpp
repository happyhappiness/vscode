static const char *sigrok_value_type(const struct sr_datafeed_analog *analog) {
  const char *s;

  if (analog->mq == SR_MQ_VOLTAGE)
    s = "voltage";
  else if (analog->mq == SR_MQ_CURRENT)
    s = "current";
  else if (analog->mq == SR_MQ_FREQUENCY)
    s = "frequency";
  else if (analog->mq == SR_MQ_POWER)
    s = "power";
  else if (analog->mq == SR_MQ_TEMPERATURE)
    s = "temperature";
  else if (analog->mq == SR_MQ_RELATIVE_HUMIDITY)
    s = "humidity";
  else if (analog->mq == SR_MQ_SOUND_PRESSURE_LEVEL)
    s = "spl";
  else
    s = "gauge";

  return s;
}