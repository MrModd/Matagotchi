#include <cstdio>
#include <stddef.h>
#include <stdint.h>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

bool saved_struct_save(const char* path, void* data, size_t size, uint8_t magic, uint8_t version) {
	std::FILE* f = std::fopen(path, "wb");
	int objects_written = std::fwrite(data, size, 1, f);
	std::fclose(f);
	return objects_written == 1;
}

bool saved_struct_load(const char* path, void* data, size_t size, uint8_t magic, uint8_t version) {
	std::FILE* f = std::fopen(path, "rb");
	int objects_written = std::fread(data, size, 1, f);
	bool fail = std::ferror(f) != 0;
	std::fclose(f);
	return objects_written == 1 and not fail;
}

#ifdef __cplusplus
}
#endif
