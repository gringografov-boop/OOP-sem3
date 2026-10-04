#include <str_ops.h>

#include <iostream>

std::size_t str_len(const char* s) {
	if (s == nullptr) return 0;
	
	size_t length = 0;
	while (s[length] != '\0') ++length;
	return length;
}

char* str_alloc(const char* src) {
	char* new_src = new char [str_len(src)+1];
	
	if (src != nullptr) {
		for (int i = 0; i < str_len(src); ++i)
			new_src[i] = src[i];
	}
	new_src[str_len(src)] = '\0';
	return new_src;
}

void str_copy(char* dst, const char* src) {
	if (dst == nullptr) {
		return;
	}

	if (src == nullptr) {
		dst[0] = '\0';
		return;
	}

	std::size_t i = 0;
	while (src[i] != '\0') {
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
}

void str_delete(char*& s) {
	delete[] s;
	s = nullptr;
}

void str_print(const char* s) {
	if (s != nullptr)std::cout << s << "\n";
}

char* str_substr(const char* s, std::size_t pos, std::size_t len) {
	const std::size_t source_length = str_len(s);

	if (s == nullptr || pos >= source_length || len == 0) {
		return str_alloc("");
	}

	const std::size_t available = source_length - pos;
	const std::size_t result_length = len < available ? len : available;
	char* result = new char[result_length + 1];

	for (std::size_t i = 0; i < result_length; ++i) {
		result[i] = s[pos + i];
	}
	result[result_length] = '\0';

	return result;
}

int str_compare(const char* a, const char* b) {
	const char* left = a != nullptr ? a : "";
	const char* right = b != nullptr ? b : "";

	std::size_t i = 0;
	while (left[i] != '\0' && right[i] != '\0' && left[i] == right[i]) {
		++i;
	}

	const unsigned char left_char = static_cast<unsigned char>(left[i]);
	const unsigned char right_char = static_cast<unsigned char>(right[i]);
	return static_cast<int>(left_char) - static_cast<int>(right_char);
}

