#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, ptr);
    return size * nmemb;
}

double get_token_price() {
    CURL *curl;
    CURLcode res;
    char data[1024] = "";
    const char *url = "https://api.example.com/token-price";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        double price = atof(data);
        return price;
    }

    return -1;
}

int main() {
    double token_price = get_token_price();
    if (token_price >= 0) {
        printf("Token Price: $%.2f\n", token_price);
    } else {
        printf("Failed to fetch token price\n");
    }
    return 0;
}
