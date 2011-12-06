drupal-xss: drupal-xss.c
		gcc -o drupal-xss drupal-xss.c -I. -lcurl
clean: 
	rm -f drupal-xss
