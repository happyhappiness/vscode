bool
store_client::Callback::pending() const
{
    return callback_handler && callback_data;
}