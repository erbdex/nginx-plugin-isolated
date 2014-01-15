#include <stdio.h>
#include <string.h>
#include <curl/curlver.h>
#include <curl/curl.h>

static char *url = "http://localhost/k/nginx_status";
//static char *user        = NULL;
//static char *pass        = NULL;
//static char *verify_peer = NULL;
//static char *verify_host = NULL;
//static char *cacert      = NULL;
static char *http_header = "cloudmagic.com";

static CURL *curl = NULL;

void main() {

    static char header_node[1024];
    struct curl_slist *curl_list = NULL;


    if (curl != NULL)
        curl_easy_cleanup(curl);

    if ((curl = curl_easy_init()) == NULL) {
        ERROR("nginx-isolated plugin: curl_easy_init failed.");
        return (-1);
    }

    strcpy(header_node, strncat("HeaderName: ", http_header, strlen(http_header)));
    curl_list = curl_slist_append(curl_list, header_node);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_list);

    if (url != NULL) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
    }




}

