#ifndef CLOJURE_NATIVE_STRING_INTERN_H
#define CLOJURE_NATIVE_STRING_INTERN_H

typedef const char* StringIntern;

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
StringIntern string_intern_n(StringIntern string, unsigned long count);
StringIntern string_intern(StringIntern string);

#endif //CLOJURE_NATIVE_STRING_INTERN_H
