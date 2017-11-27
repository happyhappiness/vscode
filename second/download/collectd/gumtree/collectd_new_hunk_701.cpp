
void cpy_log_exception(const char *context);

/* Python object declarations. */

typedef struct {
  // clang-format off
  PyObject_HEAD         /* No semicolon! */
  PyObject *parent;     /* Config */
  PyObject *key;        /* String */
  PyObject *values;     /* Sequence */
  PyObject *children;   /* Sequence */
  // clang-format on
} Config;
extern PyTypeObject ConfigType;

typedef struct {
  // clang-format off
  PyObject_HEAD /* No semicolon! */
  double time;
  // clang-format on
  char host[DATA_MAX_NAME_LEN];
  char plugin[DATA_MAX_NAME_LEN];
  char plugin_instance[DATA_MAX_NAME_LEN];
  char type[DATA_MAX_NAME_LEN];
  char type_instance[DATA_MAX_NAME_LEN];
} PluginData;
