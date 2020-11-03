#ifndef CLOJURE_NATIVE_STRING_H
#define CLOJURE_NATIVE_STRING_H

typedef const char* String;

void string_intern_init();
void string_intern_cleanup();

/**
 * Internalizes a string. This will return the same pointer for two identical strings.
 *
 * @param string A string pointer to internalize.
 * @param count Number of characters to copy from <code>string</code>.
 *              Pass <code>-1</code> to copy the whole string.
 *
 * @return A string pointer.
 */
String string_intern_n(String string, unsigned long count);
String string_intern(String string);

#endif //CLOJURE_NATIVE_STRING_H
