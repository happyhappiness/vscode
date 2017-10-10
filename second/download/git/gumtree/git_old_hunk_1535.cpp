
int expand_ref(const char *str, int len, unsigned char *sha1, char **ref);
int dwim_ref(const char *str, int len, unsigned char *sha1, char **ref);
int dwim_log(const char *str, int len, unsigned char *sha1, char **ref);

/*
 * A ref_transaction represents a collection of ref updates
 * that should succeed or fail together.
 *
 * Calling sequence
 * ----------------
 * - Allocate and initialize a `struct ref_transaction` by calling
 *   `ref_transaction_begin()`.
 *
 * - List intended ref updates by calling functions like
 *   `ref_transaction_update()` and `ref_transaction_create()`.
 *
 * - Call `ref_transaction_commit()` to execute the transaction.
 *   If this succeeds, the ref updates will have taken place and
 *   the transaction cannot be rolled back.
 *
 * - Instead of `ref_transaction_commit`, use
 *   `initial_ref_transaction_commit()` if the ref database is known
 *   to be empty (e.g. during clone).  This is likely to be much
 *   faster.
 *
 * - At any time call `ref_transaction_free()` to discard the
 *   transaction and free associated resources.  In particular,
 *   this rolls back the transaction if it has not been
 *   successfully committed.
 *
 * Error handling
 * --------------
 *
 * On error, transaction functions append a message about what
 * went wrong to the 'err' argument.  The message mentions what
