#ifdef WIN32
__declspec(dllexport)
#endif
value _SSL_load_error_strings();
#ifdef WIN32
__declspec(dllexport)
#endif
value _OpenSSL_add_all_algorithms();
#ifdef WIN32
__declspec(dllexport)
#endif
value _SSL_set_bio(value s, value rbio, value wbio);
#ifdef WIN32
__declspec(dllexport)
#endif
value _SSL_library_init();