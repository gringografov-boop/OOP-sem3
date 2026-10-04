#pragma once

#include <cstddef>

char* str_alloc(const char* src);
std::size_t str_len(const char* s);
void str_copy(char* dst, const char* src);
void str_delete(char*& s);
void str_print(const char* s);

char* str_substr(const char* s, std::size_t pos, std::size_t len);
int str_compare(const char* a, const char* b);