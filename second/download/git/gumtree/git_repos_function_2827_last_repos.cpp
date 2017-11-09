static timestamp_t log_timestamp(struct commit_reflog *log)
{
	return log->reflogs->items[log->recno].timestamp;
}