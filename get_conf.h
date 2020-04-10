#define CONF_PATH   "../../test.conf"

typedef struct {
    mys_char_t     local_ip[32];
    mys_int_t      local_port;
} conf_t;

extern conf_t g_conf;

result_t get_conf(int argc, char *argv[]);
