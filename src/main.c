#include <stdio.h>

#include "util/string.h"

#include <assert.h>

int main() {

    string_intern_init();

    String str1 = string_intern("Hello World!");
    String str2 = string_intern("Hello World!");
    String str3 = string_intern("Hello There!");

    printf("[%#010x]: %s\n[%#010x]: %s\n[%#010x]: %s\n", str1, str1, str2, str2, str3, str3);

    string_intern_cleanup();

}
