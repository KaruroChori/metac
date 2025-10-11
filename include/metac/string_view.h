#pragma once

#include <stddef.h>

typedef struct {
    const char* ptr;
    size_t len;
} StringView;
