#include "Enclave_Lab3_t.h"
#include "sgx_trts.h"
#include <string.h>

const char table[6][10] = {
	"Moscow",
	"Ufa",
	"Samara",
	"Saaratov",
	"Kazan"
};

void foo(char* buf, size_t len, size_t idx) {
	if (idx < 6) {
		const char* data_ptr = data_ptr = table[idx - 1];
		memcpy(buf, data_ptr, strlen(data_ptr));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}