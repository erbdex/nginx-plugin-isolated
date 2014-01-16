#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdint.h>

static char *url_text = "http://localhost/k/nginx_status";
//static char *user        = NULL;
//static char *pass        = NULL;
//static char *verify_peer = NULL;
//static char *verify_host = NULL;
//static char *cacert      = NULL;
static char *host_header = "cloudmagic.com";

// http://localhost/k/nginx_status -H "HOST: cloudmagic.com"

static CURL *curl = NULL;

int main() {
    char header_text[1024];
    char total_text[1024];
    struct curl_slist *curl_list = NULL;


    if (curl != NULL)
        curl_easy_cleanup(curl);

    if ((curl = curl_easy_init()) == NULL) {
        printf("\nnginx-isolated plugin: curl_easy_init failed.\n");
        return (-1);
    }

    static char *flag_text = " -H ";
    static char *quote_text = "\"";

    strncat(header_text, flag_text, strlen(flag_text));
    strncat(header_text, quote_text, strlen(quote_text));
    strncat(header_text, host_header, strlen(host_header));
    strncat(header_text, quote_text, strlen(quote_text));

    printf("\n>%s<\n", url_text);
    printf("\n>%s<\n", header_text);
    strncat(total_text, url_text, strlen(url_text));
    printf("\n>%s<\n", total_text);

    
    strncat(total_text, header_text, strlen(header_text));
    printf("\n>%s<\n", header_text);
    printf("\n%s\n", total_text);

    //    curl_list = curl_slist_append(curl_list, header_text);
    //    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_list);

    if (total_text != NULL) {
        curl_easy_setopt(curl, CURLOPT_URL, total_text);
    }

    CURLcode res;

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    printf("\nret: %s\n", res);

    curl_easy_cleanup(curl);
    curl_slist_free_all(curl_list);

}

