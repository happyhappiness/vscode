int main(int argc, const char * const *argv)
{
    apr_file_t *file;
    apr_status_t status;
    apr_pool_t *p;

    apr_initialize();
    apr_pool_create(&p, NULL);

    if (apr_file_open(&file, TESTFILE, APR_WRITE, APR_OS_DEFAULT, p) 
        != APR_SUCCESS) {
        
        exit(UNEXPECTED_ERROR);
    }
    status = apr_file_lock(file, APR_FLOCK_EXCLUSIVE | APR_FLOCK_NONBLOCK);
    if (status == APR_SUCCESS) {
        exit(SUCCESSFUL_READ);
    }
    if (APR_STATUS_IS_EAGAIN(status)) {
        exit(FAILED_READ);
    }
    exit(UNEXPECTED_ERROR);
}