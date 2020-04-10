#include "mys_du.h"
#include "mys_include.h"
#include "mys_string.h"
#include "cJSON/cJSON.h"
#include "list_head.h"
#include "vos_mem.h"
#include "mys_log.h"
#include "get_conf.h"
#include <getopt.h>

conf_t g_conf;

#define KEY_SIZE    32
#define VALUE_SIZE  32

typedef struct {
    list_head link;
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
} key_value_node_t;

static list_head g_conf_list = LIST_HEAD_INIT(g_conf_list);;

static result_t __json_to_conf(char *json_buf)
{
    cJSON *root = NULL, *item = NULL;
    result_t rc = E_OK;

    root = cJSON_Parse(json_buf);

    if (!root) {
        rc = E_BAD_CONF;
        return E_OK;
    }

    item = cJSON_GetObjectItem(root, "local_ip");

    if (item) {
        mys_snprintf(g_conf.local_ip, sizeof(g_conf.local_ip), "%s", item->valuestring);
    }

    item = cJSON_GetObjectItem(root, "local_port");
    if (item) {
        g_conf.local_port = item->valueint;
    }

//    printf("ip = %s, port = %d\n", g_conf.local_ip, g_conf.local_port);
    cJSON_Delete(root);
    return E_OK;
}


void __get_default_conf()
{
    mys_snprintf(g_conf.local_ip, sizeof(g_conf.local_ip), "%s", "127.0.0.1");
    g_conf.local_port = 10000;
}


static result_t __get_file_conf()
{
    char buf[1024] = {0};
    UINT32 len = sizeof(buf);
    cJSON  *root = NULL;
    result_t result;
    char *file_path = CONF_PATH;

    if (!fu_file_exist(file_path)) {
        return E_NOT_EXIST;
    }

    result = fu_file_get_content(file_path, (UINT8 *)buf, &len);
    if (result != E_OK) {
        return E_BAD_CONF;
    }

    return __json_to_conf(buf);
}

void __print_usage(void)
{
    BLOG("usage:\n");
    BLOG("--localip   {ip}      local bind ip\n");
    BLOG("--localport {port}    local bind port\n");
    BLOG("\n");
    
}

result_t __get_cmd_conf(int argc, char *argv[])
{
    int opt = 0;
    int c = 0;

    char *short_options = "h";
    struct option long_options[] = {
        {"help",       no_argument,            0,  'h' },
        {"localip",    required_argument,      0,  'i' },
        {"localport",  required_argument,      0,  'p' },
        {0,            0,                      0,  0 }
    };

    while ( -1 != (c = getopt_long(argc, argv, short_options, long_options, NULL))) {
        switch(c) {
        case 'h':
            __print_usage();
            break;            
        case 'i':
            mys_snprintf(g_conf.local_ip, sizeof(g_conf.local_ip), "%s", optarg);
            break;
        case 'p':
            g_conf.local_port = atoi(optarg);
            break;
            
        }
    }

    return E_OK;
}

void __show_conf(void)
{
    BLOG("final conf:\n");
    BLOG("  local ip = %s\n", g_conf.local_ip);
    BLOG("  local port = %d\n", g_conf.local_port);
}

result_t get_conf(int argc, char *argv[])
{
    __get_default_conf();
    __get_file_conf();
    __get_cmd_conf(argc, argv);
    __show_conf();
    return E_OK;
}
